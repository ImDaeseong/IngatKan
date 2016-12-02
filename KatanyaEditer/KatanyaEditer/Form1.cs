using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;

namespace KatanyaEditer
{
    public partial class Form1 : Form
    {
        private bool bLoadForm = false;

        private List<clsKata> lstkata1 = new List<clsKata>();
        private List<clsKata> lstKata2 = new List<clsKata>();

        void ClearLoadData()
        {
            lstkata1.Clear();
            lstKata2.Clear();
        }

        void LoadReadKata(string strPath, int nListType)
        {
            string strSplit = "";
            using (StreamReader sr = new StreamReader(strPath, Encoding.GetEncoding("euc-kr")))
            {
                strSplit = sr.ReadToEnd();
                sr.Close();
            }
            if (strSplit == "") return;

            string strParser = "";
            string[] blocks = strSplit.Split('{', '}');
            for (int i = 0; i < blocks.Length; i++)
            {
                strParser = blocks[i].Trim();
                if (strParser.Length == 1 || strParser.Length == 0)
                    continue;

                clsKata item = new clsKata();
                string[] rows = strParser.Split(',');
                foreach (string line in rows)
                {
                    string[] value = line.Split(':');
                    string Name = value[0].Replace("\"", "").Replace("\r", "").Replace("\n", "").Replace("\t", "").Trim();
                    string key = value[1].Replace("\"", "").Replace("\r", "").Replace("\n", "").Replace("\t", "").Trim();

                    if (Name == "kata") item.KATA = key;
                    if (Name == "arti") item.ARTI = key;
                    if (Name == "show") item.SHOW = key;
                }

                if (nListType == 1)
                    lstkata1.Add(item);
                else
                    lstKata2.Add(item);
            }          
        }
 
        void InitLoadData()
        {
            string skata1 = string.Format("{0}\\Katanya1.json", Application.StartupPath);
            string skata2 = string.Format("{0}\\Katanya2.json", Application.StartupPath);

            if (File.Exists(skata1)) LoadReadKata(skata1, 1);
            if (File.Exists(skata2)) LoadReadKata(skata2, 2);


            cboChannelname.Items.Add("kata1");
            cboChannelname.Items.Add("kata2");
            cboChannelname.SelectedIndex = 0;


            lstView.View = View.Details;
            lstView.GridLines = true;
            lstView.FullRowSelect = true;
            lstView.HeaderStyle = ColumnHeaderStyle.Clickable;
            lstView.CheckBoxes = true;
            lstView.OwnerDraw = true;

            lstView.Columns.Add("", 25, HorizontalAlignment.Left);
            lstView.Columns.Add("단어", 500, HorizontalAlignment.Left);
            lstView.Columns.Add("뜻", 600, HorizontalAlignment.Left);
            lstView.Columns.Add("숨김/보임", 100, HorizontalAlignment.Left);

            for (int i = 0; i < lstkata1.Count; i++)
            {
                ListViewItem item = new ListViewItem();
                item.Text = "";
                item.SubItems.Add(lstkata1[i].KATA);
                item.SubItems.Add(lstkata1[i].ARTI);
                item.SubItems.Add(lstkata1[i].SHOW);
                lstView.Items.Add(item);
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitLoadData();

            bLoadForm = true;
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            ClearLoadData();
        }

        private void InitChkBox()
        {
            for (int i = 0; i < lstView.Items.Count; i++)
                lstView.Items[i].Checked = false;
        }

        private void lstView_DrawColumnHeader(object sender, DrawListViewColumnHeaderEventArgs e)
        {
            if (e.ColumnIndex == 0)
            {
                e.DrawBackground();
                bool value = false;
                try
                {
                    value = Convert.ToBoolean(e.Header.Tag);
                }
                catch (Exception)
                {
                }
                CheckBoxRenderer.DrawCheckBox(e.Graphics,
                    new Point(e.Bounds.Left + 4, e.Bounds.Top + 4),
                    value ? System.Windows.Forms.VisualStyles.CheckBoxState.CheckedNormal :
                    System.Windows.Forms.VisualStyles.CheckBoxState.UncheckedNormal);
            }
            else
            {
                e.DrawDefault = true;
            }
        }

        private void lstView_DrawItem(object sender, DrawListViewItemEventArgs e)
        {
            e.DrawDefault = true;
        }

        private void lstView_DrawSubItem(object sender, DrawListViewSubItemEventArgs e)
        {
            e.DrawDefault = true;
        }

        private void lstView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstView.SelectedItems.Count > 0)
            {
                string kata = lstView.SelectedItems[0].SubItems[1].Text.ToString();
                string Arti = lstView.SelectedItems[0].SubItems[2].Text.ToString();
                string Show = lstView.SelectedItems[0].SubItems[3].Text.ToString();

                txtkata.Text = kata;
                txtArti.Text = Arti;
                txtShow.Text = Show;
            }
            else
            {
                txtkata.Text = "";
                txtArti.Text = "";
                txtShow.Text = "";
            }
        }

        private void lstView_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            if (e.Column == 0)
            {
                bool value = false;
                try
                {
                    value = Convert.ToBoolean(lstView.Columns[e.Column].Tag);
                }
                catch (Exception)
                {
                }
                lstView.Columns[e.Column].Tag = !value;
                foreach (ListViewItem item in lstView.Items)
                    item.Checked = !value;

                lstView.Invalidate();
            }
        }

        private void cboChannelname_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(!bLoadForm)return;

            lstView.Items.Clear();
            txtkata.Text = "";
            txtArti.Text = "";
            txtShow.Text = "";

            if (cboChannelname.SelectedIndex == 0)
            {
                for (int i = 0; i < lstkata1.Count; i++)
                {
                    ListViewItem item = new ListViewItem();
                    item.Text = "";
                    item.SubItems.Add(lstkata1[i].KATA);
                    item.SubItems.Add(lstkata1[i].ARTI);
                    item.SubItems.Add(lstkata1[i].SHOW);
                    lstView.Items.Add(item);
                }
            }
            else
            {
                for (int i = 0; i < lstKata2.Count; i++)
                {
                    ListViewItem item = new ListViewItem();
                    item.Text = "";
                    item.SubItems.Add(lstKata2[i].KATA);
                    item.SubItems.Add(lstKata2[i].ARTI);
                    item.SubItems.Add(lstKata2[i].SHOW);
                    lstView.Items.Add(item);
                }
            }
        }

        public bool FindKata(string kata, int nType)
        {
            bool bFind = false;

            if (nType == 0)
            {                
                for (int i = 0; i < lstkata1.Count; i++)
                {
                    if (kata == lstkata1[i].KATA)
                    {
                        bFind = true;
                        break;
                    }
                }                
            }
            else
            {                
                for (int i = 0; i < lstKata2.Count; i++)
                {
                    if (kata == lstKata2[i].KATA)
                    {
                        bFind = true;
                        break;
                    }
                }                      
            }
            return bFind;
        }

        public clsKata UpdateKata(string kata, int nType)
        {
            clsKata item = new clsKata();
            if (nType == 0)
            {
                for (int i = 0; i < lstkata1.Count; i++)
                {
                    if (kata == lstkata1[i].KATA)
                    {
                        item = lstkata1[i];
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < lstKata2.Count; i++)
                {
                    if (kata == lstKata2[i].KATA)
                    {
                        item = lstKata2[i];
                        break;
                    }
                }
            }
            return item;
        }

        public bool DeleteKata(string kata, int nType)
        {
            bool bDelete = false;
            if (nType == 0)
            {
                for (int i = 0; i < lstkata1.Count; i++)
                {
                    if (kata == lstkata1[i].KATA)
                    {
                        bDelete = true;
                        lstkata1.RemoveAt(i);
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < lstKata2.Count; i++)
                {
                    if (kata == lstKata2[i].KATA)
                    {
                        bDelete = true;
                        lstKata2.RemoveAt(i);
                        break;
                    }
                }
            }
            return bDelete;
        }
        
        private void btnSave_Click(object sender, EventArgs e)
        {
            if (txtkata.Text == "") return;
            if (txtArti.Text == "") return;
            if (txtShow.Text == "") return;

            if (cboChannelname.SelectedIndex == 0)
            {
                if (!FindKata(txtkata.Text, 0))
                {
                    clsKata item = new clsKata();
                    item.KATA = txtkata.Text;
                    item.ARTI = txtArti.Text;
                    item.SHOW = txtShow.Text;
                    lstkata1.Add(item);

                    cboChannelname_SelectedIndexChanged(null, null);
                }
                else
                {
                    MessageBox.Show("이미 존재합니다.");
                }
            }
            else
            {
                if (!FindKata(txtkata.Text, 1))
                {
                    clsKata item = new clsKata();
                    item.KATA = txtkata.Text;
                    item.ARTI = txtArti.Text;
                    item.SHOW = txtShow.Text;
                    lstKata2.Add(item);

                    cboChannelname_SelectedIndexChanged(null, null);
                }
                else
                {
                    MessageBox.Show("이미 존재합니다.");
                }            
            }

            txtkata.Text = "";
            txtArti.Text = "";
            txtShow.Text = "";
        }
        
        private void btnUpdate_Click(object sender, EventArgs e)
        {
            if (cboChannelname.SelectedIndex == 0)
            {
                if (lstView.SelectedItems.Count > 0)
                {
                    string kata = lstView.SelectedItems[0].SubItems[1].Text.ToString();
                    string Arti = lstView.SelectedItems[0].SubItems[2].Text.ToString();
                    string Show = lstView.SelectedItems[0].SubItems[3].Text.ToString();

                    clsKata item = UpdateKata(kata, 0);
                    item.KATA = txtkata.Text;
                    item.ARTI = txtArti.Text;
                    item.SHOW = txtShow.Text;

                    cboChannelname_SelectedIndexChanged(null, null);
                }
            }
            else
            {
                if (lstView.SelectedItems.Count > 0)
                {
                    string kata = lstView.SelectedItems[0].SubItems[1].Text.ToString();
                    string Arti = lstView.SelectedItems[0].SubItems[2].Text.ToString();
                    string Show = lstView.SelectedItems[0].SubItems[3].Text.ToString();

                    clsKata item = UpdateKata(kata, 1);
                    item.KATA = txtkata.Text;
                    item.ARTI = txtArti.Text;
                    item.SHOW = txtShow.Text;

                    cboChannelname_SelectedIndexChanged(null, null);
                }
            }
        }
                       
        private void btnDelete_Click(object sender, EventArgs e)
        {
            if (cboChannelname.SelectedIndex == 0)
            {
                bool bDelete = false;
                for (int i = lstView.Items.Count - 1; i >= 0; i--)
                {
                    if (lstView.Items[i].Checked)
                    {
                        string kata = lstView.Items[i].SubItems[1].Text.ToString();
                        string Arti = lstView.Items[i].SubItems[2].Text.ToString();
                        string Show = lstView.Items[i].SubItems[3].Text.ToString();
                        
                        lstView.Items.RemoveAt(i);
                        DeleteKata(kata, 0);
                        bDelete = true;
                    }
                }
                if (bDelete) cboChannelname_SelectedIndexChanged(null, null);
            }
            else
            {
                bool bDelete = false;
                for (int i = lstView.Items.Count - 1; i >= 0; i--)
                {
                    if (lstView.Items[i].Checked)
                    {
                        string kata = lstView.Items[i].SubItems[1].Text.ToString();
                        string Arti = lstView.Items[i].SubItems[2].Text.ToString();
                        string Show = lstView.Items[i].SubItems[3].Text.ToString();

                        lstView.Items.RemoveAt(i);
                        DeleteKata(kata, 1);
                        bDelete = true;
                    }
                }
                if (bDelete) cboChannelname_SelectedIndexChanged(null, null);
            }
        }

        private void btnConfirm_Click(object sender, EventArgs e)
        {
            if (cboChannelname.SelectedIndex == 0)
            {
                if (lstkata1.Count == 0)
                {
                    MessageBox.Show("저장할 내용이 없습니다.");
                    return;
                }

                string skata1 = string.Format("{0}\\Katanya1.json", Application.StartupPath);
                File.Delete(skata1);

                FileStream aFileStream = new FileStream(skata1, FileMode.OpenOrCreate);
                StreamWriter aStreamWriter = new StreamWriter(aFileStream, Encoding.GetEncoding("euc-kr"));

                aStreamWriter.Write("[");
                aStreamWriter.WriteLine();

                for (int i = 0; i < lstkata1.Count; i++)
                {
                    string sCommonStart = "{";
                    string kata = string.Format("\"kata\" :\"{0}\",", lstkata1[i].KATA);
                    string arti = string.Format("\"arti\" :\"{0}\",", lstkata1[i].ARTI);
                    string show = string.Format("\"show\" :\"{0}\"", lstkata1[i].SHOW);

                    string sCommonEnd = "";
                    if (i == (lstkata1.Count - 1))
                        sCommonEnd = " }";
                    else
                        sCommonEnd = " },";

                    string sWriteLine = sCommonStart + kata + arti + show + sCommonEnd;
                    aStreamWriter.Write(sWriteLine);
                    aStreamWriter.WriteLine();
                }

                aStreamWriter.Write("]");
                aStreamWriter.WriteLine();
                aStreamWriter.Close();

                MessageBox.Show("저장되었습니다.");
            }
            else
            {
                if (lstKata2.Count == 0)
                {
                    MessageBox.Show("저장할 내용이 없습니다.");
                    return;
                }

                string skata2 = string.Format("{0}\\Katanya2.json", Application.StartupPath);
                File.Delete(skata2);

                FileStream aFileStream = new FileStream(skata2, FileMode.OpenOrCreate);
                StreamWriter aStreamWriter = new StreamWriter(aFileStream, Encoding.GetEncoding("euc-kr"));

                aStreamWriter.Write("[");
                aStreamWriter.WriteLine();

                for (int i = 0; i < lstKata2.Count; i++)
                {
                    string sCommonStart = "{";
                    string kata = string.Format("\"kata\" :\"{0}\",", lstKata2[i].KATA);
                    string arti = string.Format("\"arti\" :\"{0}\",", lstKata2[i].ARTI);
                    string show = string.Format("\"show\" :\"{0}\"", lstKata2[i].SHOW);

                    string sCommonEnd = "";
                    if (i == (lstKata2.Count - 1))
                        sCommonEnd = " }";
                    else
                        sCommonEnd = " },";

                    string sWriteLine = sCommonStart + kata + arti + show + sCommonEnd;
                    aStreamWriter.Write(sWriteLine);
                    aStreamWriter.WriteLine();
                }

                aStreamWriter.Write("]");
                aStreamWriter.WriteLine();
                aStreamWriter.Close();

                MessageBox.Show("저장되었습니다.");
            }
        }
                
    }
}
