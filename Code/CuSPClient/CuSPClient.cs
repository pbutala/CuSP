using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Net.Sockets;
using System.Threading;

namespace CuSPClient
{
    /// <summary>
    /// Form to handle communication with CuSP Nw
    /// </summary>
    public partial class CuSPClient : Form
    {
        #region Fields
        private const String _HEADCTRL = "CTRL";
        private const String _HEADDATA = "DATA";
        private bool _runSkt = false;
        private Thread _clientService;
        private TcpClient _client;
        private delegate void delVdStr(String str);
        private bool _ctrlMsgTx = false;
        private String _ctrlMsg = String.Empty;
        private Byte[] _ctrlMsgBytes;
        private int _ctrlMsgLength;
        #endregion

        #region Properties
        #endregion

        #region Methods

        /// <summary>
        /// Creates an instance of the form
        /// </summary>
        public CuSPClient()
        {
            InitializeComponent();
            this._ssLabel.Text = String.Empty; //Status on bottom of Form
            this._ssMessage.Text = String.Empty; // Message on bottom of Form
            _ctrlMsgBytes = new Byte[1024];
        }

        private void StartClient()
        {
            if (_clientService != null)
            {
                if (!_clientService.IsAlive)
                {
                    try
                    {
                        _clientService.Abort();
                    }
                    finally
                    {
                        _clientService = null;
                    }
                }
            }
            if (_clientService == null)
            {
                try
                {
                    _client = new TcpClient("localhost", 8888);
                    _clientService = new Thread(new ThreadStart(ClientSocketService));
                    _runSkt = true;
                    _clientService.Start();
                }
                catch (Exception ex)
                {
                    _ssLabel.Text = ex.Message;
                }
            }
        }

        private void StopClient()
        {
            if (_clientService != null)
            {
                try
                {
                    _runSkt = false;
                }
                finally
                {
                    //_clientService = null;
                }
            }
        }

        private void ClientSocketService()
        {
            try
            {
                Stream s = _client.GetStream();
                StreamReader sr = new StreamReader(s);
                StreamWriter sw = new StreamWriter(s);
                sw.AutoFlush = true;

                while (_runSkt)
                {
                    if (sr.Peek() >= 0)
                    {
                        String rcvLine = sr.ReadLine();
                        ParseReceivedMessage(rcvLine);
                    }
                    if (_ctrlMsgTx)
                    {
                        //sw.WriteLine(_ctrlMsg);
                        sw.BaseStream.Write(this._ctrlMsgBytes, 0, this._ctrlMsgLength);
                        _ctrlMsgTx = false;
                    }
                }

                s.Close();
            }
            catch (Exception ex)
            {
                _ssLabel.Text = ex.Message;
            }
            finally
            {
                _client.Close();
            } 
        }

        private void ParseReceivedMessage(String msg)
        {
            if (_lblControlRx.InvokeRequired)
            {
                _lblControlRx.Invoke(new delVdStr(ParseReceivedMessage),msg);
            }
            else
            {
                try
                {
                    String[] msgs = msg.Split(';');
                    switch (msgs[0])
                    {
                        case _HEADCTRL:
                            this._lblControlRx.Text = msgs[1];
                            ParseConrolMessage(msgs[1]);
                            break;
                        case _HEADDATA:
                            this._lblDataRx.Text = msgs[1];
                            break;
                        default:
                            this._ssMessage.Text = msg;
                            break;
                    }
                }
                catch (Exception ex)
                {
                    _ssLabel.Text = ex.Message;
                }
            }
        }

        private void ParseConrolMessage(String cMsg)
        {
            try
            {
                String[] sByts = cMsg.Split(' ');
                if (sByts[2].Trim() == "41")
                {
                    this._tbValRx.Text = sByts[5];
                }
            }
            catch
            {
                this._ssLabel.Text = "Error Parsing Control Bytes";
            }
        }

        private String GetSelectedSource()
        {
            String src = String.Empty;
            if (this._rbTCS3471.Checked)
            {
                src = "tcs3471";
            }
            else if (this._rbTCS3414.Checked)
            {
                src = "tcs3414";
            }
            else if (this._rbADXL345.Checked)
            {
                src = "adxl345";
            }
            else if (this._rbITG3200.Checked)
            {
                src = "itg3200";
            }
            else
            {
                src = "none";
            }
            return src;
        }

        private String GetI2CSource()
        {
            String src = String.Empty;
            if (this._rbI2CTCS3471.Checked)
            {
                src = "tcs3471";
            }
            else if (this._rbI2CTCS3414.Checked)
            {
                src = "tcs3414";
            }
            else if (this._rbI2CADXL345.Checked)
            {
                src = "adxl345";
            }
            else if (this._rbI2CITG3200.Checked)
            {
                src = "itg3200";
            }
            else
            {
                src = "none";
            }
            return src;
        }

        #endregion

        #region Events

        private void CuSPClient_FormClosing(object sender, FormClosingEventArgs e)
        {
            _btnDisconnect_Click(this._btnDisconnect, new EventArgs());
        }

        private void _btnConnect_CheckStateChanged(object sender, EventArgs e)
        {
            /*if (_btnConnect.Checked)
            {
                StartClient();
                _btnConnect.Text = "D";
            }
            else
            {
                StopClient();
                _btnConnect.Text = "C";
            }*/
        }

        private void _btnConnect_Click(object sender, EventArgs e)
        {
            _btnConnect.Enabled = false;
            StartClient();
            _btnDisconnect.Enabled = true;
        }

        private void _btnDisconnect_Click(object sender, EventArgs e)
        {
            _btnDisconnect.Enabled = false;
            StopClient();
            _btnConnect.Enabled = true;
        }

        private void _rbSensor_CheckedChanged(object sender, EventArgs e)
        {
            if (((RadioButton)sender).Checked)
            {
                this._ctrlMsg = "cusp;1;source;"; 
                this._ctrlMsg = String.Concat(this._ctrlMsg, this.GetSelectedSource(),"\r\n");
                this._ctrlMsgLength = this._ctrlMsg.Length;
                this._ctrlMsgBytes = Encoding.ASCII.GetBytes(this._ctrlMsg);
                this._ctrlMsgTx = true;
            }
        }

        private void _rbDataOnOff_CheckedChanged(object sender, EventArgs e)
        {
            if (((RadioButton)sender).Checked)
            {
                if (sender == this._rbDataOn)
                {
                    _ctrlMsg = "cusp;1;datach;";
                    this._ctrlMsg = String.Concat(_ctrlMsg, this.GetSelectedSource(), ";on", "\r\n");
                }
                else
                {
                    _ctrlMsg = "cusp;1;datach;none;off\r\n";
                }
                this._ctrlMsgLength = this._ctrlMsg.Length;
                this._ctrlMsgBytes = Encoding.ASCII.GetBytes(this._ctrlMsg);
                this._ctrlMsgTx = true;
            }
        }

        private void _btnTx_Click(object sender, EventArgs e)
        {
            Byte rbyt,vbyt;
            bool rb = false, vb = false;
            if (rb = Byte.TryParse(this._tbRegTx.Text, System.Globalization.NumberStyles.HexNumber, null, out rbyt))
            {
                if (vb = Byte.TryParse(this._tbValTx.Text, System.Globalization.NumberStyles.HexNumber, null, out vbyt))
                {
                    this._ctrlMsg = "cusp;1;writereg;";
                    this._ctrlMsg = String.Concat(this._ctrlMsg, this.GetI2CSource());
                    this._ctrlMsg = String.Concat(_ctrlMsg, "; ; \r\n");

                    this._ctrlMsgLength = this._ctrlMsg.Length;
                    this._ctrlMsgBytes = Encoding.ASCII.GetBytes(this._ctrlMsg);
                    this._ctrlMsgBytes[this._ctrlMsgLength - 5] = rbyt;
                    this._ctrlMsgBytes[this._ctrlMsgLength - 3] = vbyt;
                    
                    this._ctrlMsgTx = true;
                }
            }
            if (!(rb && vb))
            {
                this._ssLabel.Text = "Error in Tx Params";
            }
        }

        private void _btnRx_Click(object sender, EventArgs e)
        {
            Byte rbyt;
            if (Byte.TryParse(this._tbRegRx.Text, System.Globalization.NumberStyles.HexNumber, null, out rbyt))
            {
                this._ctrlMsg = "cusp;1;readreg;";
                this._ctrlMsg = String.Concat(this._ctrlMsg, this.GetI2CSource());
                this._ctrlMsg = String.Concat(_ctrlMsg, "; \r\n");
                this._ctrlMsgLength = this._ctrlMsg.Length;
                this._ctrlMsgBytes = Encoding.ASCII.GetBytes(this._ctrlMsg);
                this._ctrlMsgBytes[this._ctrlMsgLength - 3] = rbyt;
                this._ctrlMsgTx = true;
                this._tbValRx.Clear();
            }
            else
            {
                this._ssLabel.Text = "Error in Rx Params";
            }
        }

        #endregion
    }
}
