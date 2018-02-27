using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Utilities
{
    /// <summary>
    /// Class to handle read and write to text initialization files
    /// </summary>
    public class cIniFile
    {
        #region Fields
        private String _fileName;
        private List<String> _secNames;
        private List<Hashtable> _iniValues;
        #endregion

        #region Properties
        #endregion

        #region Methods

        /// <summary>
        /// Creates an instance of FileName.ini initialization file
        /// </summary>
        /// <param name="FileName">Name of the *.ini file</param>
        public cIniFile(String FileName)
        {
            _fileName = Path.GetFileNameWithoutExtension(FileName) + ".ini";
            if (!File.Exists(_fileName))
            {
                FileStream fs = File.Create(_fileName);
                fs.Close();
            }
            _secNames = new List<string>();
            _iniValues = new List<Hashtable>();
            LoadIniFile();
        }

        public bool GetParameter<T>(String Section, String Property, ref T ptr, T Default)
        {
            bool resp = true;
            try
            {
                String sec = Section.ToLower();
                String key = Property.ToLower();
                if (_secNames.Contains(sec))
                {
                    int idx = _secNames.IndexOf(sec);
                    if (_iniValues[idx].ContainsKey(key))
                    {
                        ptr = (T)Convert.ChangeType(_iniValues[idx][key], typeof(T));
                    }
                    else
                    {
                        ptr = Default;
                        _iniValues[idx].Add(key, Default.ToString());
                        resp &= WriteParamsToFile();
                    }
                }
                else
                {
                    _secNames.Add(sec);
                    _iniValues.Add(new Hashtable());
                    resp = GetParameter<T>(sec, key, ref ptr, Default);
                }
            }
            catch (Exception)
            {
                resp = false;
            }
            return resp;
        }

        /// <summary>
        /// Writes the config/ini params to file. Overwrites existing value or creates new if it does not exist.
        /// </summary>
        /// <param name="Section">Secction name</param>
        /// <param name="Property">Property name</param>
        /// <param name="Value">Property Value</param>
        /// <returns>true if success</returns>
        private bool SetParameter(String Section, String Property, String Value)
        {
            bool resp = true;
            try
            {
                String sec = Section.ToLower();
                String key = Property.ToLower();
                if (_secNames.Contains(sec))
                {
                    int idx = _secNames.IndexOf(sec);
                    if (_iniValues[idx].ContainsKey(key))
                    {
                        _iniValues[idx].Remove(key);
                    }
                    _iniValues[idx].Add(key, Value);
                    resp = WriteParamsToFile();
                }
                else
                {
                    _secNames.Add(sec);
                    _iniValues.Add(new Hashtable());
                    SetParameter(sec, key, Value);
                }
            }
            catch (Exception)
            {
                resp = false;
            }
            return resp;
        }

        /// <summary>
        /// Deletes the config/ini param from file if it exists.
        /// </summary>
        /// <param name="Section">Secction name</param>
        /// <param name="Property">Property name</param>
        /// <returns>true if success</returns>
        private bool DeleteParameter(String Section, String Property)
        {
            bool resp = true;
            try
            {
                String sec = Section.ToLower();
                String key = Property.ToLower();
                if(_secNames.Contains(sec))
                {
                    int idx = _secNames.IndexOf(sec);
                    if (_iniValues[idx].ContainsKey(key))
                    {
                        _iniValues[idx].Remove(key);
                        if (_iniValues[idx].Count == 0)
                        {
                            _iniValues.RemoveAt(idx);
                            _secNames.RemoveAt(idx);
                        }
                        resp = WriteParamsToFile();
                    }
                }
            }
            catch (Exception)
            {
                resp = false;
            }
            return resp;
        }

        /// <summary>
        /// Loads the ini file into memory
        /// </summary>
        /// <returns>true if success</returns>
        private bool LoadIniFile()
        {
            bool resp = true;
            try
            {
                Int32 idx = -1;
                _secNames.Clear();
                _iniValues.Clear();
                using (StreamReader sr = new StreamReader(_fileName))
                {
                    while (!sr.EndOfStream)
                    {
                        String line = sr.ReadLine();
                        if (line.Contains('[')) // section name
                        {
                            String[] secsp = line.Trim().Split(new char[] { '[', ']' });
                            String sec = secsp[1];
                            _secNames.Add(sec);
                            _iniValues.Add(new Hashtable());
                            idx++;
                        }
                        else if (line.Contains('=')) // section name and value
                        {
                            String[] param = line.Split('=');
                            _iniValues[idx].Add(param[0], param[1]);
                        }
                    }
                }
            }
            catch (Exception)
            {
                resp = false;
                _secNames.Clear();
                _iniValues.Clear();
            }
            return resp;
        }

        /// <summary>
        /// Writes the params to file
        /// </summary>
        /// <returns>true if success</returns>
        private bool WriteParamsToFile()
        {
            bool resp = true;
            if (_secNames.Count > 0)
            {
                try
                {
                    using (StreamWriter sw = new StreamWriter(_fileName,false))
                    {
                        int idx = 0;
                        foreach (String sec in _secNames)
                        {
                            //String sec = _secNames[_curTableIdx];
                            sw.WriteLine("[" + sec + "]");

                            foreach(DictionaryEntry de in _iniValues[idx])
                            {
                                String line = de.Key + "=" + de.Value;
                                sw.WriteLine(line);
                            }
                            idx++;
                        }
                    }
                }
                catch (Exception)
                {
                    resp = false;
                }
            }
            return resp;
        }

        #endregion

        #region Events
        #endregion
    }
}
