<शैली गुरु>
/*==========================================================================
  NinjaSCSI-3 message handler
      By: YOKOTA Hiroshi <yokota@netlab.is.tsukuba.ac.jp>

   This software may be used and distributed according to the terms of
   the GNU General Public License.
 */

/* $Id: nsp_message.c,v 1.6 2003/07/26 14:21:09 elca Exp $ */

अटल व्योम nsp_message_in(काष्ठा scsi_cmnd *SCpnt)
अणु
	अचिन्हित पूर्णांक  base = SCpnt->device->host->io_port;
	nsp_hw_data  *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित अक्षर data_reg, control_reg;
	पूर्णांक           ret, len;

	/*
	 * XXX: NSP QUIRK
	 * NSP invoke पूर्णांकerrupts only in the हाल of scsi phase changes,
	 * thereक्रमe we should poll the scsi phase here to catch 
	 * the next "msg in" अगर exists (no scsi phase changes).
	 */
	ret = 16;
	len = 0;

	nsp_dbg(NSP_DEBUG_MSGINOCCUR, "msgin loop");
	करो अणु
		/* पढ़ो data */
		data_reg = nsp_index_पढ़ो(base, SCSIDATAIN);

		/* निश्चित ACK */
		control_reg = nsp_index_पढ़ो(base, SCSIBUSCTRL);
		control_reg |= SCSI_ACK;
		nsp_index_ग_लिखो(base, SCSIBUSCTRL, control_reg);
		nsp_negate_संकेत(SCpnt, BUSMON_REQ, "msgin<REQ>");

		data->MsgBuffer[len] = data_reg; len++;

		/* deनिश्चित ACK */
		control_reg =  nsp_index_पढ़ो(base, SCSIBUSCTRL);
		control_reg &= ~SCSI_ACK;
		nsp_index_ग_लिखो(base, SCSIBUSCTRL, control_reg);

		/* catch a next संकेत */
		ret = nsp_expect_संकेत(SCpnt, BUSPHASE_MESSAGE_IN, BUSMON_REQ);
	पूर्ण जबतक (ret > 0 && MSGBUF_SIZE > len);

	data->MsgLen = len;

पूर्ण

अटल व्योम nsp_message_out(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	पूर्णांक ret = 1;
	पूर्णांक len = data->MsgLen;

	/*
	 * XXX: NSP QUIRK
	 * NSP invoke पूर्णांकerrupts only in the हाल of scsi phase changes,
	 * thereक्रमe we should poll the scsi phase here to catch 
	 * the next "msg out" अगर exists (no scsi phase changes).
	 */

	nsp_dbg(NSP_DEBUG_MSGOUTOCCUR, "msgout loop");
	करो अणु
		अगर (nsp_xfer(SCpnt, BUSPHASE_MESSAGE_OUT)) अणु
			nsp_msg(KERN_DEBUG, "msgout: xfer short");
		पूर्ण

		/* catch a next संकेत */
		ret = nsp_expect_संकेत(SCpnt, BUSPHASE_MESSAGE_OUT, BUSMON_REQ);
	पूर्ण जबतक (ret > 0 && len-- > 0);

पूर्ण

/* end */
