using System;
using System.Windows.Forms;
using System.Drawing;
using System.Runtime.InteropServices;

namespace InstPlayer {
    public partial class Form1 : Form {
        private WinMM.MidiIn mMidiIn = new WinMM.MidiIn();
        private WinMM.WaveOut mWaveOut = new WinMM.WaveOut();

        private Bitmap bmpKeyboard = null;
        private Bitmap bmpControl = null;
        private Graphics gKeyboard = null;
        private Graphics gControl = null;

        public Form1() {
            InitializeComponent();
            setDeviceList();
            setPos();
            setSize();
            drawKeyboard();
            drawControl();
            Width = picControl.Right + 16;
            Height = menuStrip1.Height + picControl.Bottom + 39;
            timer1.Interval = 10;
            timer1.Enabled = true;
            timer1.Start();
        }

        private void Form1_SizeChanged(object sender, EventArgs e) {
            setSize();
        }

        private void Form1_Resize(object sender, EventArgs e) {
            if (Height < menuStrip1.Height + picControl.Height + 39) {
                if (picControl.Right + 16 + 17 < Width) {
                    Width = picControl.Right + 16 + 17;
                }
            } else {
                if (picControl.Right + 16 < Width) {
                    Width = picControl.Right + 16;
                }
            }
            if (Width < picControl.Right + 16) {
                if (menuStrip1.Height + picControl.Height + 39 + 17 < Height) {
                    Height = menuStrip1.Height + picControl.Height + 39 + 17;
                }
            } else {
                if (menuStrip1.Height + picControl.Height + 39 < Height) {
                    Height = menuStrip1.Height + picControl.Height + 39;
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e) {
            drawKeyboard();
            drawControl();
        }

        private void 音色ファイルを開く_Click(object sender, EventArgs e) {

        }

        private void midi_wav変換_Click(object sender, EventArgs e) {

        }

        private void デバイスDToolStripMenuItem_Click(object sender, EventArgs e) {
            setDeviceList();
        }

        private void デバイスDToolStripMenuItem_MouseHover(object sender, EventArgs e) {
            setDeviceList();
        }

        private void setDeviceList() {
            midi_in_ToolStripMenuItem.DropDownItems.Clear();
            var midiList = WinMM.MidiIn.GetDeviceList();
            for (int i = 0; i < midiList.Count; i++) {
                var str = midiList[i].Name;
                var devNum = i;
                Bitmap bmpCheck = midiList[i].Selected ? Properties.Resources.check : null;
                midi_in_ToolStripMenuItem.DropDownItems.Add(str, bmpCheck, (object snd, EventArgs ev) => {
                    try {
                        mMidiIn.MidiOpen(devNum);
                    }
                    catch (Exception ex) {
                        MessageBox.Show(ex.ToString());
                    }
                });
                midi_in_ToolStripMenuItem.DropDownItems[i].ImageScaling = ToolStripItemImageScaling.None;
            }
            if (0 == midiList.Count) {
                midi_in_ToolStripMenuItem.DropDownItems.Add("(なし)").Enabled = false;
            }

            wave_out_ToolStripMenuItem.DropDownItems.Clear();
            var waveList = WinMM.WaveOut.GetDeviceList();
            for (int i = 0; i < waveList.Count; i++) {
                var str = waveList[i].Name;
                var devNum = i;
                Bitmap bmpCheck = waveList[i].Selected ? Properties.Resources.check : null;
                wave_out_ToolStripMenuItem.DropDownItems.Add(str, bmpCheck, (object snd, EventArgs ev) => {
                    try {
                        mWaveOut.WaveOpen(devNum);
                    }
                    catch (Exception ex) {
                        MessageBox.Show(ex.ToString());
                    }
                });
                wave_out_ToolStripMenuItem.DropDownItems[i].ImageScaling = ToolStripItemImageScaling.None;
            }
        }

        private void setPos() {
            picChannelNum.Top = 0;
            picChannelNum.Left = 0;
            picChannelNum.Width = Properties.Resources.channel_num.Width;
            picChannelNum.Height = Properties.Resources.channel_num.Height;

            picChannelOnOff.Top = 0;
            picChannelOnOff.Left = picChannelNum.Right;
            picChannelOnOff.Width = Properties.Resources.channel_on_off.Width;
            picChannelOnOff.Height = Properties.Resources.channel_on_off.Height;

            picKeyboard.Top = 0;
            picKeyboard.Left = picChannelOnOff.Right;
            picKeyboard.Width = Properties.Resources.keyboard.Width;
            picKeyboard.Height = Properties.Resources.keyboard.Height;

            picInstName.Top = 0;
            picInstName.Left = picKeyboard.Right;
            picInstName.Width = Properties.Resources.inst_name.Width;
            picInstName.Height = Properties.Resources.inst_name.Height;

            picControl.Top = 0;
            picControl.Left = picInstName.Right;
            picControl.Width = Properties.Resources.control.Width;
            picControl.Height = Properties.Resources.control.Height;
        }

        private void setSize() {
            panel1.Top = menuStrip1.Bottom;
            panel1.Left = 0;
            panel1.Width = Width - 16;
            panel1.Height = Height - menuStrip1.Height - 39;

            if (null != picKeyboard.Image) {
                picKeyboard.Image.Dispose();
                picKeyboard.Image = null;
                gKeyboard.Dispose();
                gKeyboard = null;
                bmpKeyboard.Dispose();
                bmpKeyboard = null;
            }
            bmpKeyboard = new Bitmap(picKeyboard.Width, picKeyboard.Height);
            gKeyboard = Graphics.FromImage(bmpKeyboard);

            if (null != picControl.Image) {
                picControl.Image.Dispose();
                picControl.Image = null;
                gControl.Dispose();
                gControl = null;
                bmpControl.Dispose();
                bmpControl = null;
            }
            bmpControl = new Bitmap(picControl.Width, picControl.Height);
            gControl = Graphics.FromImage(bmpControl);

            drawKeyboard();
            drawControl();
        }

        private void drawKeyboard() {
            gKeyboard.Clear(Color.Transparent);

            var ppKeyboard = mMidiIn.KeyboardPtr();
            for (int chNum = 0; chNum < 16; chNum++) {
                var pKeyboard = Marshal.PtrToStructure<IntPtr>(ppKeyboard + Marshal.SizeOf<IntPtr>() * chNum);
                for (int noteNum = 0; noteNum < 127; noteNum++) {
                    var keyState = Marshal.PtrToStructure<byte>(pKeyboard + noteNum);
                    if (0 == keyState) {
                        continue;
                    }
                    var note = noteNum % 12;
                    var oct_x = noteNum / 12 * 28;
                    var ch_y = 30 * chNum + 8;
                    var brush = 1 == keyState ? Brushes.Red : Brushes.Blue;
                    switch (note) {
                    case 0:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 1, ch_y + 9, 3, 5));
                        break;
                    case 1:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 3, ch_y, 3, 9));
                        break;
                    case 2:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 5, ch_y + 9, 3, 5));
                        break;
                    case 3:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 7, ch_y, 3, 9));
                        break;
                    case 4:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 9, ch_y + 9, 3, 5));
                        break;
                    case 5:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 13, ch_y + 9, 3, 5));
                        break;
                    case 6:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 15, ch_y, 3, 9));
                        break;
                    case 7:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 17, ch_y + 9, 3, 5));
                        break;
                    case 8:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 19, ch_y, 3, 9));
                        break;
                    case 9:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 21, ch_y + 9, 3, 5));
                        break;
                    case 10:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 23, ch_y, 3, 9));
                        break;
                    case 11:
                        gKeyboard.FillRectangle(brush, new Rectangle(oct_x + 25, ch_y + 9, 3, 5));
                        break;
                    }
                }
            }
            picKeyboard.Image = bmpKeyboard;
        }

        private unsafe void drawControl() {
            gControl.Clear(Color.Transparent);

            var ppChannelParam = mMidiIn.ChannelParamPtr();
            for (int chNum = 0; chNum < 16; chNum++) {
                var para = ppChannelParam[chNum];
                var ch_y = 30 * chNum;

                var knob_x = 20;
                var th = (2 * Math.PI * (para->vol - 0.5) / 127.0 - Math.PI) * 4 / 5.0;
                var x = (int)(-1 + 7 * Math.Sin(th));
                var y = (int)(12 - 7 * Math.Cos(th));
                gControl.FillRectangle(Brushes.GreenYellow, new Rectangle(knob_x + x, ch_y + y, 3, 3));

                knob_x = 44;
                th = (2 * Math.PI * (para->exp - 0.5) / 127.0 - Math.PI) * 4 / 5.0;
                x = (int)(-1 + 7 * Math.Sin(th));
                y = (int)(12 - 7 * Math.Cos(th));
                gControl.FillRectangle(Brushes.GreenYellow, new Rectangle(knob_x + x, ch_y + y, 3, 3));

                knob_x = 68;
                th = (2 * Math.PI * (para->pan - 0.5) / 127.0 - Math.PI) * 4 / 5.0;
                x = (int)(-1 + 7 * Math.Sin(th));
                y = (int)(12 - 7 * Math.Cos(th));
                gControl.FillRectangle(Brushes.GreenYellow, new Rectangle(knob_x + x, ch_y + y, 3, 3));

                knob_x = 100;
                th = (2 * Math.PI * (para->rev - 0.5) / 127.0 - Math.PI) * 4 / 5.0;
                x = (int)(-1 + 7 * Math.Sin(th));
                y = (int)(12 - 7 * Math.Cos(th));
                gControl.FillRectangle(Brushes.Blue, new Rectangle(knob_x + x, ch_y + y, 3, 3));

                knob_x = 124;
                th = (2 * Math.PI * (para->cho - 0.5) / 127.0 - Math.PI) * 4 / 5.0;
                x = (int)(-1 + 7 * Math.Sin(th));
                y = (int)(12 - 7 * Math.Cos(th));
                gControl.FillRectangle(Brushes.Blue, new Rectangle(knob_x + x, ch_y + y, 3, 3));

                knob_x = 148;
                th = (2 * Math.PI * (para->del - 0.5) / 127.0 - Math.PI) * 4 / 5.0;
                x = (int)(-1 + 7 * Math.Sin(th));
                y = (int)(12 - 7 * Math.Cos(th));
                gControl.FillRectangle(Brushes.Blue, new Rectangle(knob_x + x, ch_y + y, 3, 3));

                knob_x = 180;
                th = (2 * Math.PI * (para->fc - 0.5) / 127.0 - Math.PI) * 4 / 5.0;
                x = (int)(-1 + 7 * Math.Sin(th));
                y = (int)(12 - 7 * Math.Cos(th));
                gControl.FillRectangle(Brushes.Yellow, new Rectangle(knob_x + x, ch_y + y, 3, 3));

                knob_x = 204;
                th = (2 * Math.PI * (para->fq - 0.5) / 127.0 - Math.PI) * 4 / 5.0;
                x = (int)(-1 + 7 * Math.Sin(th));
                y = (int)(12 - 7 * Math.Cos(th));
                gControl.FillRectangle(Brushes.Yellow, new Rectangle(knob_x + x, ch_y + y, 3, 3));

                knob_x = 228;
                th = (2 * Math.PI * (para->mod - 0.5) / 127.0 - Math.PI) * 4 / 5.0;
                x = (int)(-1 + 7 * Math.Sin(th));
                y = (int)(12 - 7 * Math.Cos(th));
                gControl.FillRectangle(Brushes.Yellow, new Rectangle(knob_x + x, ch_y + y, 3, 3));
            }

            picControl.Image = bmpControl;
        }
    }
}
