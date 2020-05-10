using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace WinMM {
    public enum MMResult : uint {
        MMSYSERR_NOERROR = 0,
        MMSYSERR_ERROR = 1,
        MMSYSERR_BADDEVICEID = 2,
        MMSYSERR_NOTENABLED = 3,
        MMSYSERR_ALLOCATED = 4,
        MMSYSERR_INVALHANDLE = 5,
        MMSYSERR_NODRIVER = 6,
        MMSYSERR_NOMEM = 7,
        MMSYSERR_NOTSUPPORTED = 8,
        MMSYSERR_BADERRNUM = 9,
        MMSYSERR_INVALFLAG = 10,
        MMSYSERR_INVALPARAM = 11,
        MMSYSERR_HANDLEBUSY = 12,
        MMSYSERR_INVALIDALIAS = 13,
        MMSYSERR_BADDB = 14,
        MMSYSERR_KEYNOTFOUND = 15,
        MMSYSERR_READERROR = 16,
        MMSYSERR_WRITEERROR = 17,
        MMSYSERR_DELETEERROR = 18,
        MMSYSERR_VALNOTFOUND = 19,
        MMSYSERR_NODRIVERCB = 20,
        WAVERR_BADFORMAT = 32,
        WAVERR_STILLPLAYING = 33,
        WAVERR_UNPREPARED = 34
    }

    public enum MMCallback : uint {
        CALLBACK_NULL       = 0x00000000,    /* no callback */
        CALLBACK_WINDOW     = 0x00010000,    /* dwCallback is a HWND */
        CALLBACK_TASK       = 0x00020000,    /* dwCallback is a HTASK */
        CALLBACK_FUNCTION   = 0x00030000     /* dwCallback is a FARPROC */
    }

    public unsafe class MidiIn {
        [StructLayout(LayoutKind.Sequential, Pack = 4)]
        public struct MidiInCapsA {
            public ushort wMid;
            public ushort wPid;
            public uint vDriverVersion;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public byte[] szPname;
            public uint dwSupport;
        }

        public class DeviceItem {
            public string Name { get; set; }
            public uint ID { get; set; }
            public bool Selected { get; set; }
        }

        private static DeviceItem mSelectedDevice = new DeviceItem {
            Name = "MIDI Mapper",
            ID = 0xFFFFFFFF,
            Selected = true
        };

        [StructLayout(LayoutKind.Sequential, Pack = 4)]
        public struct INST_ID {
            public byte isDrum;
            public byte progNum;
            public byte bankMSB;
            public byte bankLSB;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 4)]
        public struct CHANNEL_PARAM {
            public INST_ID id;

            public byte vol;
            public byte exp;
            public byte pan;
            public byte rev;

            public byte cho;
            public byte del;
            public byte fq;
            public byte fc;

            public byte mod;
            public byte reserved;
            public byte attack;
            public byte release;

            public byte hold;
            public byte rpnMsb;
            public byte rpnLsb;
            public byte bendRange;

            public int pitch;
        }

        /// <summary>
        /// MIDI入力ポートの数を取得します。
        /// </summary>
        [DllImport("winmm.dll", EntryPoint = "midiInGetNumDevs")]
        [return: MarshalAs(UnmanagedType.U4)]
        private static extern uint midiInGetNumDevs();

        /// <summary>
        /// MIDI入力ポートの情報を取得します。
        /// </summary>
        [DllImport("winmm.dll", EntryPoint = "midiInGetDevCaps", CharSet = CharSet.Ansi)]
        [return: MarshalAs(UnmanagedType.U4)]
        private static extern MMResult midiInGetDevCaps([MarshalAs(UnmanagedType.U4)]uint uDeviceID, ref MidiInCapsA lpMidiInCaps, [MarshalAs(UnmanagedType.U4)]uint cbMidiInCaps);

        [DllImport("winmm.dll", EntryPoint = "midiInUnprepareHeader", CharSet = CharSet.Ansi)]
        [return: MarshalAs(UnmanagedType.U4)]
        private static extern MMResult midiInUnprepareHeader(uint phmi, IntPtr lpMidiInHdr, uint uSize);

        [DllImport("WaveOut.dll", EntryPoint = "waveout_midiOpen")]
        [return: MarshalAs(UnmanagedType.U4)]
        private static extern void waveout_midiOpen(uint devNum);

        [DllImport("WaveOut.dll", EntryPoint = "waveout_getChannelParamPtr")]
        private static extern CHANNEL_PARAM** waveout_getChannelParamPtr();

        [DllImport("WaveOut.dll", EntryPoint = "waveout_getKeyboardPtr")]
        private static extern IntPtr waveout_getKeyboardPtr();

        /// <summary>
        /// MIDI入力ポートの数を取得します。
        /// </summary>
        public static int GetPortCount() {
            return (int)midiInGetNumDevs();
        }

        /// <summary>
        /// MIDI入力ポートの情報を取得します。
        /// </summary>
        public static MidiInCapsA GetPortInformation(uint portNum) {
            var caps = new MidiInCapsA();
            midiInGetDevCaps(portNum, ref caps, (uint)Marshal.SizeOf(typeof(MidiInCapsA)));
            return caps;
        }

        /// <summary>
        /// MIDI入力ポートのリストを取得します。
        /// </summary>
        public static List<DeviceItem> GetDeviceList() {
            var list = new List<DeviceItem>();

            int count = GetPortCount();
            for (uint i = 0; i < count; i++) {
                var item = new DeviceItem();
                var caps = GetPortInformation(i);
                item.Name = Encoding.Default.GetString(caps.szPname);
                item.ID = i;
                var remIdx = item.Name.IndexOf("\0");
                if (0 <= remIdx) {
                    item.Name = item.Name.Remove(remIdx);
                }
                list.Add(item);
            }

            for (int i = 0; i < list.Count; i++) {
                var dev = list[i];
                if (dev.ID == mSelectedDevice.ID && dev.Name == mSelectedDevice.Name) {
                    list[i].Selected = true;
                } else {
                    list[i].Selected = false;
                }
            }

            return list;
        }

        /// <summary>
        /// MIDI入力ポートを開く
        /// </summary>
        public void MidiOpen(int num) {
            var list = GetDeviceList();
            if (list.Count <= num) {
                return;
            }
            mSelectedDevice = list[num];
            waveout_getChannelParamPtr();
            waveout_midiOpen(mSelectedDevice.ID);
        }

        public CHANNEL_PARAM** ChannelParamPtr() {
            return waveout_getChannelParamPtr();
        }

        public IntPtr KeyboardPtr() {
            return waveout_getKeyboardPtr();
        }
    }
}
