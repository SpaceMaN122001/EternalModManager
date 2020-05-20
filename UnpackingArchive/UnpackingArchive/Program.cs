using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SharpCompress.Archives;
using SharpCompress.Writers;
using SharpCompress.Readers;
using System.Diagnostics;

namespace UnpackingArchive
{
    class Program
    {
        static void Main(string[] args)
        {
            Unzip(args[0], args[1]);

            foreach (Process proc in Process.GetProcessesByName("UnpackingArchive"))
            {
                proc.Kill();
            }
        }

        static void Unzip(string pathToArchive, string pathToExtract)
        {
            using (var archive = ArchiveFactory.Open(pathToArchive))
            {
                foreach (var entry in archive.Entries)
                {
                    if (!entry.IsDirectory)
                        entry.WriteToDirectory(pathToExtract, new SharpCompress.Common.ExtractionOptions() { ExtractFullPath = true, Overwrite = true });
                }
            }
        }
    }
}
