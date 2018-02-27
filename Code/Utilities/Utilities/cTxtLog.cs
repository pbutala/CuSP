using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;

namespace Utilities
{
    /// <summary>
    /// Utility class that handles all text logs
    /// </summary>
    public class cTxtLog
    {
        #region Fields
        private String _logFile;
        private Thread _wrtRtn;
        private List<String> _lstLog = new List<string>(50);
        private bool _stopLog;
        private Mutex _mtxLog = new Mutex();

        private const int LOGWAITMS = 500;
        #endregion

        #region Properties
        #endregion

        #region Methods
        /// <summary>
        /// Creates an instance of a cTxtLog class
        /// </summary>
        /// <param name="logName">Log name. Will be used to create log file in executable directory</param>
        public cTxtLog(String logName)
        {
            _logFile = System.IO.Path.Combine(Directory.GetCurrentDirectory(), logName);
        }

        /// <summary>
        /// Creates an instance of a cTxtLog class
        /// </summary>
        /// <param name="logDir">Log Directory</param>
        /// <param name="logName">Log File</param>
        public cTxtLog(String logDir, String logName)
        {
            _logFile = System.IO.Path.Combine(logDir, logName);
        }

        /// <summary>
        /// Initializes the class instance
        /// </summary>
        public void StartLog()
        {
            try
            {
                if ((this._wrtRtn != null) && (this._wrtRtn.ThreadState != ThreadState.Stopped))
                {
                    System.Threading.Thread.Sleep(700);
                    this._wrtRtn.Abort();
                }
            }
            catch (Exception)
            {
            }
            finally
            {
                this._stopLog = false;
                this._wrtRtn = new Thread(new ThreadStart(LogRoutine));
                if (this._wrtRtn.ThreadState == ThreadState.Unstarted)
                {
                    this._wrtRtn.Start();
                }
            }
        }

        /// <summary>
        /// Stops the log.
        /// </summary>
        public void StopLog()
        {
            this._stopLog = true;
        }

        /// <summary>
        /// Starts the log routine
        /// </summary>
        private void LogRoutine()
        {
            try
            {
                using (StreamWriter sw = new StreamWriter(_logFile, true))
                {
                    while (!_stopLog)
                    {
                        if (this._lstLog.Count > 0)
                        {
                            if (this._mtxLog.WaitOne())
                            {
                                for (int idx = 0; idx < this._lstLog.Count; idx++)
                                {
                                    sw.WriteLine(this._lstLog[idx]);
                                }
                                this._lstLog.Clear();
                            }
                            this._mtxLog.ReleaseMutex();
                        }
                        Thread.Sleep(LOGWAITMS);
                    }
                }
            }
            catch (Exception)
            {
            }
        }

        /// <summary>
        /// Writes log to file
        /// </summary>
        /// <param name="log"></param>
        public void WriteLog(String log)
        {
            if (this._mtxLog.WaitOne())
            {
                this._lstLog.Add(log);
            }
            this._mtxLog.ReleaseMutex();
        }
        #endregion

        #region Events
        #endregion
    }
}
