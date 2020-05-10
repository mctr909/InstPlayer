namespace InstPlayer {
    partial class Form1 {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent() {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.ファイルFToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.開くOToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mIDIWave変換TToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.デバイスDToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.midi_in_ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.wave_out_ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.picControl = new System.Windows.Forms.PictureBox();
            this.picInstName = new System.Windows.Forms.PictureBox();
            this.picKeyboard = new System.Windows.Forms.PictureBox();
            this.picChannelOnOff = new System.Windows.Forms.PictureBox();
            this.picChannelNum = new System.Windows.Forms.PictureBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picControl)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picInstName)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picKeyboard)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picChannelOnOff)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picChannelNum)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.SystemColors.Control;
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ファイルFToolStripMenuItem,
            this.デバイスDToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(920, 40);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // ファイルFToolStripMenuItem
            // 
            this.ファイルFToolStripMenuItem.BackColor = System.Drawing.SystemColors.Control;
            this.ファイルFToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.開くOToolStripMenuItem,
            this.mIDIWave変換TToolStripMenuItem});
            this.ファイルFToolStripMenuItem.ForeColor = System.Drawing.Color.Black;
            this.ファイルFToolStripMenuItem.Name = "ファイルFToolStripMenuItem";
            this.ファイルFToolStripMenuItem.Size = new System.Drawing.Size(121, 36);
            this.ファイルFToolStripMenuItem.Text = "ファイル(F)";
            // 
            // 開くOToolStripMenuItem
            // 
            this.開くOToolStripMenuItem.Name = "開くOToolStripMenuItem";
            this.開くOToolStripMenuItem.Size = new System.Drawing.Size(318, 38);
            this.開くOToolStripMenuItem.Text = "音色ファイルを開く(O)";
            this.開くOToolStripMenuItem.Click += new System.EventHandler(this.音色ファイルを開く_Click);
            // 
            // mIDIWave変換TToolStripMenuItem
            // 
            this.mIDIWave変換TToolStripMenuItem.Name = "mIDIWave変換TToolStripMenuItem";
            this.mIDIWave変換TToolStripMenuItem.Size = new System.Drawing.Size(318, 38);
            this.mIDIWave変換TToolStripMenuItem.Text = "midi -> wav変換(T)";
            this.mIDIWave変換TToolStripMenuItem.Click += new System.EventHandler(this.midi_wav変換_Click);
            // 
            // デバイスDToolStripMenuItem
            // 
            this.デバイスDToolStripMenuItem.BackColor = System.Drawing.SystemColors.Control;
            this.デバイスDToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.midi_in_ToolStripMenuItem,
            this.wave_out_ToolStripMenuItem});
            this.デバイスDToolStripMenuItem.ForeColor = System.Drawing.Color.Black;
            this.デバイスDToolStripMenuItem.Name = "デバイスDToolStripMenuItem";
            this.デバイスDToolStripMenuItem.Size = new System.Drawing.Size(131, 36);
            this.デバイスDToolStripMenuItem.Text = "デバイス(D)";
            this.デバイスDToolStripMenuItem.Click += new System.EventHandler(this.デバイスDToolStripMenuItem_Click);
            this.デバイスDToolStripMenuItem.MouseHover += new System.EventHandler(this.デバイスDToolStripMenuItem_MouseHover);
            // 
            // midi_in_ToolStripMenuItem
            // 
            this.midi_in_ToolStripMenuItem.Name = "midi_in_ToolStripMenuItem";
            this.midi_in_ToolStripMenuItem.Size = new System.Drawing.Size(242, 38);
            this.midi_in_ToolStripMenuItem.Text = "MIDI入力(I)";
            // 
            // wave_out_ToolStripMenuItem
            // 
            this.wave_out_ToolStripMenuItem.Name = "wave_out_ToolStripMenuItem";
            this.wave_out_ToolStripMenuItem.Size = new System.Drawing.Size(242, 38);
            this.wave_out_ToolStripMenuItem.Text = "音声出力(O)";
            // 
            // picControl
            // 
            this.picControl.BackgroundImage = global::InstPlayer.Properties.Resources.control;
            this.picControl.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.picControl.Location = new System.Drawing.Point(583, 3);
            this.picControl.Name = "picControl";
            this.picControl.Size = new System.Drawing.Size(260, 496);
            this.picControl.TabIndex = 5;
            this.picControl.TabStop = false;
            // 
            // picInstName
            // 
            this.picInstName.BackgroundImage = global::InstPlayer.Properties.Resources.inst_name;
            this.picInstName.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.picInstName.Location = new System.Drawing.Point(434, 3);
            this.picInstName.Name = "picInstName";
            this.picInstName.Size = new System.Drawing.Size(132, 496);
            this.picInstName.TabIndex = 4;
            this.picInstName.TabStop = false;
            // 
            // picKeyboard
            // 
            this.picKeyboard.BackgroundImage = global::InstPlayer.Properties.Resources.keyboard;
            this.picKeyboard.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.picKeyboard.Location = new System.Drawing.Point(102, 3);
            this.picKeyboard.Name = "picKeyboard";
            this.picKeyboard.Size = new System.Drawing.Size(326, 496);
            this.picKeyboard.TabIndex = 3;
            this.picKeyboard.TabStop = false;
            // 
            // picChannelOnOff
            // 
            this.picChannelOnOff.BackgroundImage = global::InstPlayer.Properties.Resources.channel_on_off;
            this.picChannelOnOff.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.picChannelOnOff.Location = new System.Drawing.Point(56, 3);
            this.picChannelOnOff.Name = "picChannelOnOff";
            this.picChannelOnOff.Size = new System.Drawing.Size(40, 496);
            this.picChannelOnOff.TabIndex = 2;
            this.picChannelOnOff.TabStop = false;
            // 
            // picChannelNum
            // 
            this.picChannelNum.BackgroundImage = global::InstPlayer.Properties.Resources.channel_num;
            this.picChannelNum.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.picChannelNum.Location = new System.Drawing.Point(3, 3);
            this.picChannelNum.Name = "picChannelNum";
            this.picChannelNum.Size = new System.Drawing.Size(47, 496);
            this.picChannelNum.TabIndex = 1;
            this.picChannelNum.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Controls.Add(this.picKeyboard);
            this.panel1.Controls.Add(this.picControl);
            this.panel1.Controls.Add(this.picChannelNum);
            this.panel1.Controls.Add(this.picInstName);
            this.panel1.Controls.Add(this.picChannelOnOff);
            this.panel1.Location = new System.Drawing.Point(12, 60);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(862, 517);
            this.panel1.TabIndex = 6;
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(920, 645);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.SizeChanged += new System.EventHandler(this.Form1_SizeChanged);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picControl)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picInstName)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picKeyboard)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picChannelOnOff)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picChannelNum)).EndInit();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem ファイルFToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 開くOToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mIDIWave変換TToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem デバイスDToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem midi_in_ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem wave_out_ToolStripMenuItem;
        private System.Windows.Forms.PictureBox picChannelNum;
        private System.Windows.Forms.PictureBox picChannelOnOff;
        private System.Windows.Forms.PictureBox picKeyboard;
        private System.Windows.Forms.PictureBox picInstName;
        private System.Windows.Forms.PictureBox picControl;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Timer timer1;
    }
}

