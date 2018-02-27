namespace CuSPClient
{
    partial class CuSPClient
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CuSPClient));
            this._gbSensor = new System.Windows.Forms.GroupBox();
            this._rbTCS3414 = new System.Windows.Forms.RadioButton();
            this._rbNone = new System.Windows.Forms.RadioButton();
            this._rbITG3200 = new System.Windows.Forms.RadioButton();
            this._rbADXL345 = new System.Windows.Forms.RadioButton();
            this._rbTCS3471 = new System.Windows.Forms.RadioButton();
            this._gbDataChannel = new System.Windows.Forms.GroupBox();
            this._rbDataOff = new System.Windows.Forms.RadioButton();
            this._rbDataOn = new System.Windows.Forms.RadioButton();
            this._lblControlRx = new System.Windows.Forms.Label();
            this._lblCR = new System.Windows.Forms.Label();
            this._lblDR = new System.Windows.Forms.Label();
            this._lblDataRx = new System.Windows.Forms.Label();
            this._statusStrip = new System.Windows.Forms.StatusStrip();
            this._ssLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this._ssMessage = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this._btnConnect = new System.Windows.Forms.ToolStripButton();
            this._btnDisconnect = new System.Windows.Forms.ToolStripButton();
            this._gbI2CSensor = new System.Windows.Forms.GroupBox();
            this._rbI2CTCS3414 = new System.Windows.Forms.RadioButton();
            this._rbI2CITG3200 = new System.Windows.Forms.RadioButton();
            this._rbI2CADXL345 = new System.Windows.Forms.RadioButton();
            this._rbI2CTCS3471 = new System.Windows.Forms.RadioButton();
            this._gbI2CTx = new System.Windows.Forms.GroupBox();
            this._btnTx = new System.Windows.Forms.Button();
            this._lblValTx = new System.Windows.Forms.Label();
            this._tbValTx = new System.Windows.Forms.TextBox();
            this._lblRegTx = new System.Windows.Forms.Label();
            this._tbRegTx = new System.Windows.Forms.TextBox();
            this._gbI2CRx = new System.Windows.Forms.GroupBox();
            this._btnRx = new System.Windows.Forms.Button();
            this._lblValRx = new System.Windows.Forms.Label();
            this._tbValRx = new System.Windows.Forms.TextBox();
            this._lblRegRx = new System.Windows.Forms.Label();
            this._tbRegRx = new System.Windows.Forms.TextBox();
            this._gbSensor.SuspendLayout();
            this._gbDataChannel.SuspendLayout();
            this._statusStrip.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this._gbI2CSensor.SuspendLayout();
            this._gbI2CTx.SuspendLayout();
            this._gbI2CRx.SuspendLayout();
            this.SuspendLayout();
            // 
            // _gbSensor
            // 
            this._gbSensor.Controls.Add(this._rbTCS3414);
            this._gbSensor.Controls.Add(this._rbNone);
            this._gbSensor.Controls.Add(this._rbITG3200);
            this._gbSensor.Controls.Add(this._rbADXL345);
            this._gbSensor.Controls.Add(this._rbTCS3471);
            this._gbSensor.Location = new System.Drawing.Point(12, 28);
            this._gbSensor.Name = "_gbSensor";
            this._gbSensor.Size = new System.Drawing.Size(97, 135);
            this._gbSensor.TabIndex = 0;
            this._gbSensor.TabStop = false;
            this._gbSensor.Text = "Data: Sensor";
            // 
            // _rbTCS3414
            // 
            this._rbTCS3414.AutoSize = true;
            this._rbTCS3414.Location = new System.Drawing.Point(6, 42);
            this._rbTCS3414.Name = "_rbTCS3414";
            this._rbTCS3414.Size = new System.Drawing.Size(70, 17);
            this._rbTCS3414.TabIndex = 4;
            this._rbTCS3414.Text = "TCS3414";
            this._rbTCS3414.UseVisualStyleBackColor = true;
            this._rbTCS3414.CheckedChanged += new System.EventHandler(this._rbSensor_CheckedChanged);
            // 
            // _rbNone
            // 
            this._rbNone.AutoSize = true;
            this._rbNone.Checked = true;
            this._rbNone.Location = new System.Drawing.Point(6, 111);
            this._rbNone.Name = "_rbNone";
            this._rbNone.Size = new System.Drawing.Size(51, 17);
            this._rbNone.TabIndex = 3;
            this._rbNone.TabStop = true;
            this._rbNone.Text = "None";
            this._rbNone.UseVisualStyleBackColor = true;
            this._rbNone.CheckedChanged += new System.EventHandler(this._rbSensor_CheckedChanged);
            // 
            // _rbITG3200
            // 
            this._rbITG3200.AutoSize = true;
            this._rbITG3200.Location = new System.Drawing.Point(6, 88);
            this._rbITG3200.Name = "_rbITG3200";
            this._rbITG3200.Size = new System.Drawing.Size(67, 17);
            this._rbITG3200.TabIndex = 2;
            this._rbITG3200.Text = "ITG3200";
            this._rbITG3200.UseVisualStyleBackColor = true;
            this._rbITG3200.CheckedChanged += new System.EventHandler(this._rbSensor_CheckedChanged);
            // 
            // _rbADXL345
            // 
            this._rbADXL345.AutoSize = true;
            this._rbADXL345.Location = new System.Drawing.Point(6, 65);
            this._rbADXL345.Name = "_rbADXL345";
            this._rbADXL345.Size = new System.Drawing.Size(71, 17);
            this._rbADXL345.TabIndex = 1;
            this._rbADXL345.Text = "ADXL345";
            this._rbADXL345.UseVisualStyleBackColor = true;
            this._rbADXL345.CheckedChanged += new System.EventHandler(this._rbSensor_CheckedChanged);
            // 
            // _rbTCS3471
            // 
            this._rbTCS3471.AutoSize = true;
            this._rbTCS3471.Location = new System.Drawing.Point(6, 19);
            this._rbTCS3471.Name = "_rbTCS3471";
            this._rbTCS3471.Size = new System.Drawing.Size(70, 17);
            this._rbTCS3471.TabIndex = 0;
            this._rbTCS3471.Text = "TCS3471";
            this._rbTCS3471.UseVisualStyleBackColor = true;
            this._rbTCS3471.CheckedChanged += new System.EventHandler(this._rbSensor_CheckedChanged);
            // 
            // _gbDataChannel
            // 
            this._gbDataChannel.Controls.Add(this._rbDataOff);
            this._gbDataChannel.Controls.Add(this._rbDataOn);
            this._gbDataChannel.Location = new System.Drawing.Point(115, 28);
            this._gbDataChannel.Name = "_gbDataChannel";
            this._gbDataChannel.Size = new System.Drawing.Size(97, 135);
            this._gbDataChannel.TabIndex = 1;
            this._gbDataChannel.TabStop = false;
            this._gbDataChannel.Text = "Data: Channel";
            // 
            // _rbDataOff
            // 
            this._rbDataOff.AutoSize = true;
            this._rbDataOff.Checked = true;
            this._rbDataOff.Location = new System.Drawing.Point(6, 42);
            this._rbDataOff.Name = "_rbDataOff";
            this._rbDataOff.Size = new System.Drawing.Size(39, 17);
            this._rbDataOff.TabIndex = 1;
            this._rbDataOff.TabStop = true;
            this._rbDataOff.Text = "Off";
            this._rbDataOff.UseVisualStyleBackColor = true;
            this._rbDataOff.CheckedChanged += new System.EventHandler(this._rbDataOnOff_CheckedChanged);
            // 
            // _rbDataOn
            // 
            this._rbDataOn.AutoSize = true;
            this._rbDataOn.Location = new System.Drawing.Point(6, 19);
            this._rbDataOn.Name = "_rbDataOn";
            this._rbDataOn.Size = new System.Drawing.Size(39, 17);
            this._rbDataOn.TabIndex = 0;
            this._rbDataOn.Text = "On";
            this._rbDataOn.UseVisualStyleBackColor = true;
            this._rbDataOn.CheckedChanged += new System.EventHandler(this._rbDataOnOff_CheckedChanged);
            // 
            // _lblControlRx
            // 
            this._lblControlRx.AutoSize = true;
            this._lblControlRx.Location = new System.Drawing.Point(265, 72);
            this._lblControlRx.Name = "_lblControlRx";
            this._lblControlRx.Size = new System.Drawing.Size(56, 13);
            this._lblControlRx.TabIndex = 3;
            this._lblControlRx.Text = "Control Rx";
            // 
            // _lblCR
            // 
            this._lblCR.AutoSize = true;
            this._lblCR.Location = new System.Drawing.Point(218, 72);
            this._lblCR.Name = "_lblCR";
            this._lblCR.Size = new System.Drawing.Size(41, 13);
            this._lblCR.TabIndex = 5;
            this._lblCR.Text = "Ctrl Rx:";
            // 
            // _lblDR
            // 
            this._lblDR.AutoSize = true;
            this._lblDR.Location = new System.Drawing.Point(218, 49);
            this._lblDR.Name = "_lblDR";
            this._lblDR.Size = new System.Drawing.Size(33, 13);
            this._lblDR.TabIndex = 7;
            this._lblDR.Text = "Data:";
            // 
            // _lblDataRx
            // 
            this._lblDataRx.AutoSize = true;
            this._lblDataRx.Location = new System.Drawing.Point(265, 49);
            this._lblDataRx.Name = "_lblDataRx";
            this._lblDataRx.Size = new System.Drawing.Size(46, 13);
            this._lblDataRx.TabIndex = 6;
            this._lblDataRx.Text = "Data Rx";
            // 
            // _statusStrip
            // 
            this._statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this._ssLabel,
            this._ssMessage});
            this._statusStrip.Location = new System.Drawing.Point(0, 296);
            this._statusStrip.Name = "_statusStrip";
            this._statusStrip.Size = new System.Drawing.Size(444, 22);
            this._statusStrip.TabIndex = 8;
            this._statusStrip.Text = "statusStrip1";
            // 
            // _ssLabel
            // 
            this._ssLabel.Name = "_ssLabel";
            this._ssLabel.Size = new System.Drawing.Size(39, 17);
            this._ssLabel.Text = "Status";
            // 
            // _ssMessage
            // 
            this._ssMessage.Name = "_ssMessage";
            this._ssMessage.Size = new System.Drawing.Size(390, 17);
            this._ssMessage.Spring = true;
            this._ssMessage.Text = "Message";
            this._ssMessage.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this._btnConnect,
            this._btnDisconnect});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(444, 25);
            this.toolStrip1.TabIndex = 9;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // _btnConnect
            // 
            this._btnConnect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this._btnConnect.Image = ((System.Drawing.Image)(resources.GetObject("_btnConnect.Image")));
            this._btnConnect.ImageTransparentColor = System.Drawing.Color.Magenta;
            this._btnConnect.Name = "_btnConnect";
            this._btnConnect.Size = new System.Drawing.Size(23, 22);
            this._btnConnect.Text = "C";
            this._btnConnect.ToolTipText = "Connect to Server";
            this._btnConnect.CheckStateChanged += new System.EventHandler(this._btnConnect_CheckStateChanged);
            this._btnConnect.Click += new System.EventHandler(this._btnConnect_Click);
            // 
            // _btnDisconnect
            // 
            this._btnDisconnect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this._btnDisconnect.Enabled = false;
            this._btnDisconnect.Image = ((System.Drawing.Image)(resources.GetObject("_btnDisconnect.Image")));
            this._btnDisconnect.ImageTransparentColor = System.Drawing.Color.Magenta;
            this._btnDisconnect.Name = "_btnDisconnect";
            this._btnDisconnect.Size = new System.Drawing.Size(23, 22);
            this._btnDisconnect.Text = "D";
            this._btnDisconnect.ToolTipText = "Disconnect from Server";
            this._btnDisconnect.Click += new System.EventHandler(this._btnDisconnect_Click);
            // 
            // _gbI2CSensor
            // 
            this._gbI2CSensor.Controls.Add(this._rbI2CTCS3414);
            this._gbI2CSensor.Controls.Add(this._rbI2CITG3200);
            this._gbI2CSensor.Controls.Add(this._rbI2CADXL345);
            this._gbI2CSensor.Controls.Add(this._rbI2CTCS3471);
            this._gbI2CSensor.Location = new System.Drawing.Point(12, 169);
            this._gbI2CSensor.Name = "_gbI2CSensor";
            this._gbI2CSensor.Size = new System.Drawing.Size(97, 124);
            this._gbI2CSensor.TabIndex = 10;
            this._gbI2CSensor.TabStop = false;
            this._gbI2CSensor.Text = "I2C: Sensor";
            // 
            // _rbI2CTCS3414
            // 
            this._rbI2CTCS3414.AutoSize = true;
            this._rbI2CTCS3414.Location = new System.Drawing.Point(6, 42);
            this._rbI2CTCS3414.Name = "_rbI2CTCS3414";
            this._rbI2CTCS3414.Size = new System.Drawing.Size(70, 17);
            this._rbI2CTCS3414.TabIndex = 3;
            this._rbI2CTCS3414.Text = "TCS3414";
            this._rbI2CTCS3414.UseVisualStyleBackColor = true;
            // 
            // _rbI2CITG3200
            // 
            this._rbI2CITG3200.AutoSize = true;
            this._rbI2CITG3200.Location = new System.Drawing.Point(6, 88);
            this._rbI2CITG3200.Name = "_rbI2CITG3200";
            this._rbI2CITG3200.Size = new System.Drawing.Size(67, 17);
            this._rbI2CITG3200.TabIndex = 2;
            this._rbI2CITG3200.Text = "ITG3200";
            this._rbI2CITG3200.UseVisualStyleBackColor = true;
            // 
            // _rbI2CADXL345
            // 
            this._rbI2CADXL345.AutoSize = true;
            this._rbI2CADXL345.Location = new System.Drawing.Point(6, 65);
            this._rbI2CADXL345.Name = "_rbI2CADXL345";
            this._rbI2CADXL345.Size = new System.Drawing.Size(71, 17);
            this._rbI2CADXL345.TabIndex = 1;
            this._rbI2CADXL345.Text = "ADXL345";
            this._rbI2CADXL345.UseVisualStyleBackColor = true;
            // 
            // _rbI2CTCS3471
            // 
            this._rbI2CTCS3471.AutoSize = true;
            this._rbI2CTCS3471.Checked = true;
            this._rbI2CTCS3471.Location = new System.Drawing.Point(6, 19);
            this._rbI2CTCS3471.Name = "_rbI2CTCS3471";
            this._rbI2CTCS3471.Size = new System.Drawing.Size(70, 17);
            this._rbI2CTCS3471.TabIndex = 0;
            this._rbI2CTCS3471.TabStop = true;
            this._rbI2CTCS3471.Text = "TCS3471";
            this._rbI2CTCS3471.UseVisualStyleBackColor = true;
            // 
            // _gbI2CTx
            // 
            this._gbI2CTx.Controls.Add(this._btnTx);
            this._gbI2CTx.Controls.Add(this._lblValTx);
            this._gbI2CTx.Controls.Add(this._tbValTx);
            this._gbI2CTx.Controls.Add(this._lblRegTx);
            this._gbI2CTx.Controls.Add(this._tbRegTx);
            this._gbI2CTx.Location = new System.Drawing.Point(115, 169);
            this._gbI2CTx.Name = "_gbI2CTx";
            this._gbI2CTx.Size = new System.Drawing.Size(97, 124);
            this._gbI2CTx.TabIndex = 11;
            this._gbI2CTx.TabStop = false;
            this._gbI2CTx.Text = "I2C: Tx";
            // 
            // _btnTx
            // 
            this._btnTx.Location = new System.Drawing.Point(56, 67);
            this._btnTx.Name = "_btnTx";
            this._btnTx.Size = new System.Drawing.Size(35, 20);
            this._btnTx.TabIndex = 4;
            this._btnTx.Text = "Tx";
            this._btnTx.UseVisualStyleBackColor = true;
            this._btnTx.Click += new System.EventHandler(this._btnTx_Click);
            // 
            // _lblValTx
            // 
            this._lblValTx.AutoSize = true;
            this._lblValTx.Location = new System.Drawing.Point(6, 44);
            this._lblValTx.Name = "_lblValTx";
            this._lblValTx.Size = new System.Drawing.Size(45, 13);
            this._lblValTx.TabIndex = 3;
            this._lblValTx.Text = "Val:   0x";
            // 
            // _tbValTx
            // 
            this._tbValTx.Location = new System.Drawing.Point(56, 41);
            this._tbValTx.MaxLength = 2;
            this._tbValTx.Name = "_tbValTx";
            this._tbValTx.Size = new System.Drawing.Size(35, 20);
            this._tbValTx.TabIndex = 2;
            this._tbValTx.Text = "00";
            // 
            // _lblRegTx
            // 
            this._lblRegTx.AutoSize = true;
            this._lblRegTx.Location = new System.Drawing.Point(6, 21);
            this._lblRegTx.Name = "_lblRegTx";
            this._lblRegTx.Size = new System.Drawing.Size(44, 13);
            this._lblRegTx.TabIndex = 1;
            this._lblRegTx.Text = "Reg: 0x";
            // 
            // _tbRegTx
            // 
            this._tbRegTx.Location = new System.Drawing.Point(56, 18);
            this._tbRegTx.MaxLength = 2;
            this._tbRegTx.Name = "_tbRegTx";
            this._tbRegTx.Size = new System.Drawing.Size(35, 20);
            this._tbRegTx.TabIndex = 0;
            this._tbRegTx.Text = "00";
            // 
            // _gbI2CRx
            // 
            this._gbI2CRx.Controls.Add(this._btnRx);
            this._gbI2CRx.Controls.Add(this._lblValRx);
            this._gbI2CRx.Controls.Add(this._tbValRx);
            this._gbI2CRx.Controls.Add(this._lblRegRx);
            this._gbI2CRx.Controls.Add(this._tbRegRx);
            this._gbI2CRx.Location = new System.Drawing.Point(218, 169);
            this._gbI2CRx.Name = "_gbI2CRx";
            this._gbI2CRx.Size = new System.Drawing.Size(97, 124);
            this._gbI2CRx.TabIndex = 12;
            this._gbI2CRx.TabStop = false;
            this._gbI2CRx.Text = "I2C: Rx";
            // 
            // _btnRx
            // 
            this._btnRx.Location = new System.Drawing.Point(56, 67);
            this._btnRx.Name = "_btnRx";
            this._btnRx.Size = new System.Drawing.Size(35, 20);
            this._btnRx.TabIndex = 8;
            this._btnRx.Text = "Rx";
            this._btnRx.UseVisualStyleBackColor = true;
            this._btnRx.Click += new System.EventHandler(this._btnRx_Click);
            // 
            // _lblValRx
            // 
            this._lblValRx.AutoSize = true;
            this._lblValRx.Location = new System.Drawing.Point(6, 44);
            this._lblValRx.Name = "_lblValRx";
            this._lblValRx.Size = new System.Drawing.Size(45, 13);
            this._lblValRx.TabIndex = 7;
            this._lblValRx.Text = "Val:   0x";
            // 
            // _tbValRx
            // 
            this._tbValRx.Enabled = false;
            this._tbValRx.Location = new System.Drawing.Point(56, 41);
            this._tbValRx.MaxLength = 2;
            this._tbValRx.Name = "_tbValRx";
            this._tbValRx.Size = new System.Drawing.Size(35, 20);
            this._tbValRx.TabIndex = 6;
            // 
            // _lblRegRx
            // 
            this._lblRegRx.AutoSize = true;
            this._lblRegRx.Location = new System.Drawing.Point(6, 21);
            this._lblRegRx.Name = "_lblRegRx";
            this._lblRegRx.Size = new System.Drawing.Size(44, 13);
            this._lblRegRx.TabIndex = 5;
            this._lblRegRx.Text = "Reg: 0x";
            // 
            // _tbRegRx
            // 
            this._tbRegRx.Location = new System.Drawing.Point(56, 18);
            this._tbRegRx.MaxLength = 2;
            this._tbRegRx.Name = "_tbRegRx";
            this._tbRegRx.Size = new System.Drawing.Size(35, 20);
            this._tbRegRx.TabIndex = 4;
            this._tbRegRx.Text = "00";
            // 
            // CuSPClient
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(444, 318);
            this.Controls.Add(this._gbI2CRx);
            this.Controls.Add(this._gbI2CTx);
            this.Controls.Add(this._gbI2CSensor);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this._statusStrip);
            this.Controls.Add(this._lblDR);
            this.Controls.Add(this._lblDataRx);
            this.Controls.Add(this._lblCR);
            this.Controls.Add(this._lblControlRx);
            this.Controls.Add(this._gbDataChannel);
            this.Controls.Add(this._gbSensor);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "CuSPClient";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "CuSP Client";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.CuSPClient_FormClosing);
            this._gbSensor.ResumeLayout(false);
            this._gbSensor.PerformLayout();
            this._gbDataChannel.ResumeLayout(false);
            this._gbDataChannel.PerformLayout();
            this._statusStrip.ResumeLayout(false);
            this._statusStrip.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this._gbI2CSensor.ResumeLayout(false);
            this._gbI2CSensor.PerformLayout();
            this._gbI2CTx.ResumeLayout(false);
            this._gbI2CTx.PerformLayout();
            this._gbI2CRx.ResumeLayout(false);
            this._gbI2CRx.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox _gbSensor;
        private System.Windows.Forms.RadioButton _rbITG3200;
        private System.Windows.Forms.RadioButton _rbADXL345;
        private System.Windows.Forms.RadioButton _rbTCS3471;
        private System.Windows.Forms.GroupBox _gbDataChannel;
        private System.Windows.Forms.RadioButton _rbDataOff;
        private System.Windows.Forms.RadioButton _rbDataOn;
        private System.Windows.Forms.Label _lblControlRx;
        private System.Windows.Forms.Label _lblCR;
        private System.Windows.Forms.Label _lblDR;
        private System.Windows.Forms.Label _lblDataRx;
        private System.Windows.Forms.StatusStrip _statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel _ssLabel;
        private System.Windows.Forms.RadioButton _rbNone;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton _btnConnect;
        private System.Windows.Forms.ToolStripStatusLabel _ssMessage;
        private System.Windows.Forms.ToolStripButton _btnDisconnect;
        private System.Windows.Forms.GroupBox _gbI2CSensor;
        private System.Windows.Forms.RadioButton _rbI2CITG3200;
        private System.Windows.Forms.RadioButton _rbI2CADXL345;
        private System.Windows.Forms.RadioButton _rbI2CTCS3471;
        private System.Windows.Forms.GroupBox _gbI2CTx;
        private System.Windows.Forms.GroupBox _gbI2CRx;
        private System.Windows.Forms.Label _lblValTx;
        private System.Windows.Forms.TextBox _tbValTx;
        private System.Windows.Forms.Label _lblRegTx;
        private System.Windows.Forms.TextBox _tbRegTx;
        private System.Windows.Forms.Label _lblValRx;
        private System.Windows.Forms.TextBox _tbValRx;
        private System.Windows.Forms.Label _lblRegRx;
        private System.Windows.Forms.TextBox _tbRegRx;
        private System.Windows.Forms.Button _btnTx;
        private System.Windows.Forms.Button _btnRx;
        private System.Windows.Forms.RadioButton _rbTCS3414;
        private System.Windows.Forms.RadioButton _rbI2CTCS3414;
    }
}

