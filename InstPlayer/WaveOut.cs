using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace WinMM {
    class WaveOut {
        [StructLayout(LayoutKind.Sequential, Pack = 2, CharSet = CharSet.Auto)]
        public struct WaveOutCaps {
            public short wMid;
            public short wPid;
            public uint vDriverVersion;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public byte[] szPname;
            public int dwFormats;
            public short wChannels;
            public short wReserved1;
            public int dwSupport;
        }

        public class DeviceItem {
            public string Name { get; set; }
            public uint ID { get; set; }
            public bool Selected { get; set; }
        }

        public static int NumDevs {
            get { return waveOutGetNumDevs(); }
        }

        public const uint WaveMapper = 0xFFFFFFFF;

        private static DeviceItem mSelectedDevice = new DeviceItem {
            Name = "Wave Mapper",
            ID = 0xFFFFFFFF,
            Selected = true
        };

        [DllImport("winmm.dll", EntryPoint = "waveOutGetNumDevs", CharSet = CharSet.Ansi)]
        private static extern int waveOutGetNumDevs();

        /// <summary>
        /// MIDI入力ポートの情報を取得します。
        /// </summary>
        [DllImport("winmm.dll", EntryPoint = "waveOutGetDevCaps", CharSet = CharSet.Ansi)]
        [return: MarshalAs(UnmanagedType.U4)]
        private static extern MMResult waveOutGetDevCaps([MarshalAs(UnmanagedType.U4)]uint uDeviceID, ref WaveOutCaps pwoc, [MarshalAs(UnmanagedType.U4)]int cbwoc);

        /// <summary>
        /// WAVE出力ポートのリストを取得します。
        /// </summary>
        public static List<DeviceItem> GetDeviceList() {
            var deviceList = new List<DeviceItem>();
            var waveOutCaps = new WaveOutCaps();

            var item = new DeviceItem();
            item.Name = "Wave Mapper";
            item.ID = WaveMapper;
            deviceList.Add(item);

            for (uint id = 0; id < NumDevs; id++) {
                var ret = waveOutGetDevCaps(id, ref waveOutCaps, Marshal.SizeOf(typeof(WaveOutCaps)));
                var tmpName = Encoding.Default.GetString(waveOutCaps.szPname);
                var remIdx = tmpName.IndexOf("\0");
                if (0 <= remIdx) {
                    tmpName = tmpName.Remove(remIdx);
                }
                item = new DeviceItem();
                item.Name = (ret == MMResult.MMSYSERR_NOERROR) ? tmpName : "No Name";
                item.ID = id;
                deviceList.Add(item);
            }

            for (int i = 0; i < deviceList.Count; i++) {
                var dev = deviceList[i];
                if (dev.ID == mSelectedDevice.ID && dev.Name == mSelectedDevice.Name) {
                    deviceList[i].Selected = true;
                } else {
                    deviceList[i].Selected = false;
                }
            }

            return deviceList;
        }

        /// <summary>
        /// WAVE出力ポートを開く
        /// </summary>
        public void WaveOpen(int num) {
            var list = GetDeviceList();
            if (list.Count <= num) {
                return;
            }
            mSelectedDevice = list[num];
        }
    }
}
