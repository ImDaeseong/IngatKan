namespace KatanyaEditer
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.cboChannelname = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.lstView = new System.Windows.Forms.ListView();
            this.txtkata = new System.Windows.Forms.TextBox();
            this.txtArti = new System.Windows.Forms.TextBox();
            this.txtShow = new System.Windows.Forms.TextBox();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.btnConfirm = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.btnUpdate = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // cboChannelname
            // 
            this.cboChannelname.FormattingEnabled = true;
            this.cboChannelname.Location = new System.Drawing.Point(66, 14);
            this.cboChannelname.Name = "cboChannelname";
            this.cboChannelname.Size = new System.Drawing.Size(231, 20);
            this.cboChannelname.TabIndex = 0;
            this.cboChannelname.SelectedIndexChanged += new System.EventHandler(this.cboChannelname_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(16, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "선택 :";
            // 
            // lstView
            // 
            this.lstView.Location = new System.Drawing.Point(15, 40);
            this.lstView.Name = "lstView";
            this.lstView.Size = new System.Drawing.Size(1194, 292);
            this.lstView.TabIndex = 2;
            this.lstView.UseCompatibleStateImageBehavior = false;
            this.lstView.DrawColumnHeader += new System.Windows.Forms.DrawListViewColumnHeaderEventHandler(this.lstView_DrawColumnHeader);
            this.lstView.DrawItem += new System.Windows.Forms.DrawListViewItemEventHandler(this.lstView_DrawItem);
            this.lstView.SelectedIndexChanged += new System.EventHandler(this.lstView_SelectedIndexChanged);
            this.lstView.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.lstView_ColumnClick);
            this.lstView.DrawSubItem += new System.Windows.Forms.DrawListViewSubItemEventHandler(this.lstView_DrawSubItem);
            // 
            // txtkata
            // 
            this.txtkata.Location = new System.Drawing.Point(86, 345);
            this.txtkata.Name = "txtkata";
            this.txtkata.Size = new System.Drawing.Size(1122, 21);
            this.txtkata.TabIndex = 3;
            // 
            // txtArti
            // 
            this.txtArti.Location = new System.Drawing.Point(86, 375);
            this.txtArti.Name = "txtArti";
            this.txtArti.Size = new System.Drawing.Size(1122, 21);
            this.txtArti.TabIndex = 4;
            // 
            // txtShow
            // 
            this.txtShow.Location = new System.Drawing.Point(86, 405);
            this.txtShow.Name = "txtShow";
            this.txtShow.Size = new System.Drawing.Size(1122, 21);
            this.txtShow.TabIndex = 5;
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(86, 435);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(120, 23);
            this.btnSave.TabIndex = 16;
            this.btnSave.Text = "신규";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.Location = new System.Drawing.Point(371, 435);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(135, 23);
            this.btnDelete.TabIndex = 17;
            this.btnDelete.Text = "삭제";
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // btnConfirm
            // 
            this.btnConfirm.Location = new System.Drawing.Point(1080, 435);
            this.btnConfirm.Name = "btnConfirm";
            this.btnConfirm.Size = new System.Drawing.Size(129, 23);
            this.btnConfirm.TabIndex = 18;
            this.btnConfirm.Text = "저장";
            this.btnConfirm.UseVisualStyleBackColor = true;
            this.btnConfirm.Click += new System.EventHandler(this.btnConfirm_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 349);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 12);
            this.label2.TabIndex = 19;
            this.label2.Text = "단어 :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 380);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(21, 12);
            this.label3.TabIndex = 20;
            this.label3.Text = "뜻:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 411);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 12);
            this.label4.TabIndex = 21;
            this.label4.Text = "보임/숨김:";
            // 
            // btnUpdate
            // 
            this.btnUpdate.Location = new System.Drawing.Point(221, 435);
            this.btnUpdate.Name = "btnUpdate";
            this.btnUpdate.Size = new System.Drawing.Size(135, 23);
            this.btnUpdate.TabIndex = 32;
            this.btnUpdate.Text = "수정";
            this.btnUpdate.UseVisualStyleBackColor = true;
            this.btnUpdate.Click += new System.EventHandler(this.btnUpdate_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1221, 470);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnConfirm);
            this.Controls.Add(this.btnDelete);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnUpdate);
            this.Controls.Add(this.txtShow);
            this.Controls.Add(this.txtArti);
            this.Controls.Add(this.txtkata);
            this.Controls.Add(this.lstView);
            this.Controls.Add(this.cboChannelname);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "kataEditor";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtkata;
        private System.Windows.Forms.TextBox txtArti;
        private System.Windows.Forms.TextBox txtShow;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cboChannelname;
        private System.Windows.Forms.ListView lstView;
        private System.Windows.Forms.Button btnUpdate;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.Button btnConfirm;
    }
}

