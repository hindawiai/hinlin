<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_vda.c
 *      esas2r driver VDA firmware पूर्णांकerface functions
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  NO WARRANTY
 *  THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 *  CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 *  LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 *  MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 *  solely responsible क्रम determining the appropriateness of using and
 *  distributing the Program and assumes all risks associated with its
 *  exercise of rights under this Agreement, including but not limited to
 *  the risks and costs of program errors, damage to or loss of data,
 *  programs or equipment, and unavailability or पूर्णांकerruption of operations.
 *
 *  DISCLAIMER OF LIABILITY
 *  NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 *  सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 *  HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#समावेश "esas2r.h"

अटल u8 esas2r_vdaioctl_versions[] = अणु
	ATTO_VDA_VER_UNSUPPORTED,
	ATTO_VDA_FLASH_VER,
	ATTO_VDA_VER_UNSUPPORTED,
	ATTO_VDA_VER_UNSUPPORTED,
	ATTO_VDA_CLI_VER,
	ATTO_VDA_VER_UNSUPPORTED,
	ATTO_VDA_CFG_VER,
	ATTO_VDA_MGT_VER,
	ATTO_VDA_GSV_VER
पूर्ण;

अटल व्योम clear_vda_request(काष्ठा esas2r_request *rq);

अटल व्योम esas2r_complete_vda_ioctl(काष्ठा esas2r_adapter *a,
				      काष्ठा esas2r_request *rq);

/* Prepare a VDA IOCTL request to be sent to the firmware. */
bool esas2r_process_vda_ioctl(काष्ठा esas2r_adapter *a,
			      काष्ठा atto_ioctl_vda *vi,
			      काष्ठा esas2r_request *rq,
			      काष्ठा esas2r_sg_context *sgc)
अणु
	u32 datalen = 0;
	काष्ठा atto_vda_sge *firstsg = शून्य;
	u8 vercnt = (u8)ARRAY_SIZE(esas2r_vdaioctl_versions);

	vi->status = ATTO_STS_SUCCESS;
	vi->vda_status = RS_PENDING;

	अगर (vi->function >= vercnt) अणु
		vi->status = ATTO_STS_INV_FUNC;
		वापस false;
	पूर्ण

	अगर (vi->version > esas2r_vdaioctl_versions[vi->function]) अणु
		vi->status = ATTO_STS_INV_VERSION;
		वापस false;
	पूर्ण

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags)) अणु
		vi->status = ATTO_STS_DEGRADED;
		वापस false;
	पूर्ण

	अगर (vi->function != VDA_FUNC_SCSI)
		clear_vda_request(rq);

	rq->vrq->scsi.function = vi->function;
	rq->पूर्णांकerrupt_cb = esas2r_complete_vda_ioctl;
	rq->पूर्णांकerrupt_cx = vi;

	चयन (vi->function) अणु
	हाल VDA_FUNC_FLASH:

		अगर (vi->cmd.flash.sub_func != VDA_FLASH_FREAD
		    && vi->cmd.flash.sub_func != VDA_FLASH_FWRITE
		    && vi->cmd.flash.sub_func != VDA_FLASH_FINFO) अणु
			vi->status = ATTO_STS_INV_FUNC;
			वापस false;
		पूर्ण

		अगर (vi->cmd.flash.sub_func != VDA_FLASH_FINFO)
			datalen = vi->data_length;

		rq->vrq->flash.length = cpu_to_le32(datalen);
		rq->vrq->flash.sub_func = vi->cmd.flash.sub_func;

		स_नकल(rq->vrq->flash.data.file.file_name,
		       vi->cmd.flash.data.file.file_name,
		       माप(vi->cmd.flash.data.file.file_name));

		firstsg = rq->vrq->flash.data.file.sge;
		अवरोध;

	हाल VDA_FUNC_CLI:

		datalen = vi->data_length;

		rq->vrq->cli.cmd_rsp_len =
			cpu_to_le32(vi->cmd.cli.cmd_rsp_len);
		rq->vrq->cli.length = cpu_to_le32(datalen);

		firstsg = rq->vrq->cli.sge;
		अवरोध;

	हाल VDA_FUNC_MGT:
	अणु
		u8 *cmdcurr_offset = sgc->cur_offset
				     - दुरत्व(काष्ठा atto_ioctl_vda, data)
				     + दुरत्व(काष्ठा atto_ioctl_vda, cmd)
				     + दुरत्व(काष्ठा atto_ioctl_vda_mgt_cmd,
						data);
		/*
		 * build the data payload SGL here first since
		 * esas2r_sgc_init() will modअगरy the S/G list offset क्रम the
		 * management SGL (which is built below where the data SGL is
		 * usually built).
		 */

		अगर (vi->data_length) अणु
			u32 payldlen = 0;

			अगर (vi->cmd.mgt.mgt_func == VDAMGT_DEV_HEALTH_REQ
			    || vi->cmd.mgt.mgt_func == VDAMGT_DEV_METRICS) अणु
				rq->vrq->mgt.payld_sglst_offset =
					(u8)दुरत्व(काष्ठा atto_vda_mgmt_req,
						     payld_sge);

				payldlen = vi->data_length;
				datalen = vi->cmd.mgt.data_length;
			पूर्ण अन्यथा अगर (vi->cmd.mgt.mgt_func == VDAMGT_DEV_INFO2
				   || vi->cmd.mgt.mgt_func ==
				   VDAMGT_DEV_INFO2_BYADDR) अणु
				datalen = vi->data_length;
				cmdcurr_offset = sgc->cur_offset;
			पूर्ण अन्यथा अणु
				vi->status = ATTO_STS_INV_PARAM;
				वापस false;
			पूर्ण

			/* Setup the length so building the payload SGL works */
			rq->vrq->mgt.length = cpu_to_le32(datalen);

			अगर (payldlen) अणु
				rq->vrq->mgt.payld_length =
					cpu_to_le32(payldlen);

				esas2r_sgc_init(sgc, a, rq,
						rq->vrq->mgt.payld_sge);
				sgc->length = payldlen;

				अगर (!esas2r_build_sg_list(a, rq, sgc)) अणु
					vi->status = ATTO_STS_OUT_OF_RSRC;
					वापस false;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			datalen = vi->cmd.mgt.data_length;

			rq->vrq->mgt.length = cpu_to_le32(datalen);
		पूर्ण

		/*
		 * Now that the payload SGL is built, अगर any, setup to build
		 * the management SGL.
		 */
		firstsg = rq->vrq->mgt.sge;
		sgc->cur_offset = cmdcurr_offset;

		/* Finish initializing the management request. */
		rq->vrq->mgt.mgt_func = vi->cmd.mgt.mgt_func;
		rq->vrq->mgt.scan_generation = vi->cmd.mgt.scan_generation;
		rq->vrq->mgt.dev_index =
			cpu_to_le32(vi->cmd.mgt.dev_index);

		esas2r_nuxi_mgt_data(rq->vrq->mgt.mgt_func, &vi->cmd.mgt.data);
		अवरोध;
	पूर्ण

	हाल VDA_FUNC_CFG:

		अगर (vi->data_length
		    || vi->cmd.cfg.data_length == 0) अणु
			vi->status = ATTO_STS_INV_PARAM;
			वापस false;
		पूर्ण

		अगर (vi->cmd.cfg.cfg_func == VDA_CFG_INIT) अणु
			vi->status = ATTO_STS_INV_FUNC;
			वापस false;
		पूर्ण

		rq->vrq->cfg.sub_func = vi->cmd.cfg.cfg_func;
		rq->vrq->cfg.length = cpu_to_le32(vi->cmd.cfg.data_length);

		अगर (vi->cmd.cfg.cfg_func == VDA_CFG_GET_INIT) अणु
			स_नकल(&rq->vrq->cfg.data,
			       &vi->cmd.cfg.data,
			       vi->cmd.cfg.data_length);

			esas2r_nuxi_cfg_data(rq->vrq->cfg.sub_func,
					     &rq->vrq->cfg.data);
		पूर्ण अन्यथा अणु
			vi->status = ATTO_STS_INV_FUNC;

			वापस false;
		पूर्ण

		अवरोध;

	हाल VDA_FUNC_GSV:

		vi->cmd.gsv.rsp_len = vercnt;

		स_नकल(vi->cmd.gsv.version_info, esas2r_vdaioctl_versions,
		       vercnt);

		vi->vda_status = RS_SUCCESS;
		अवरोध;

	शेष:

		vi->status = ATTO_STS_INV_FUNC;
		वापस false;
	पूर्ण

	अगर (datalen) अणु
		esas2r_sgc_init(sgc, a, rq, firstsg);
		sgc->length = datalen;

		अगर (!esas2r_build_sg_list(a, rq, sgc)) अणु
			vi->status = ATTO_STS_OUT_OF_RSRC;
			वापस false;
		पूर्ण
	पूर्ण

	esas2r_start_request(a, rq);

	वापस true;
पूर्ण

अटल व्योम esas2r_complete_vda_ioctl(काष्ठा esas2r_adapter *a,
				      काष्ठा esas2r_request *rq)
अणु
	काष्ठा atto_ioctl_vda *vi = (काष्ठा atto_ioctl_vda *)rq->पूर्णांकerrupt_cx;

	vi->vda_status = rq->req_stat;

	चयन (vi->function) अणु
	हाल VDA_FUNC_FLASH:

		अगर (vi->cmd.flash.sub_func == VDA_FLASH_FINFO
		    || vi->cmd.flash.sub_func == VDA_FLASH_FREAD)
			vi->cmd.flash.data.file.file_size =
				le32_to_cpu(rq->func_rsp.flash_rsp.file_size);

		अवरोध;

	हाल VDA_FUNC_MGT:

		vi->cmd.mgt.scan_generation =
			rq->func_rsp.mgt_rsp.scan_generation;
		vi->cmd.mgt.dev_index = le16_to_cpu(
			rq->func_rsp.mgt_rsp.dev_index);

		अगर (vi->data_length == 0)
			vi->cmd.mgt.data_length =
				le32_to_cpu(rq->func_rsp.mgt_rsp.length);

		esas2r_nuxi_mgt_data(rq->vrq->mgt.mgt_func, &vi->cmd.mgt.data);
		अवरोध;

	हाल VDA_FUNC_CFG:

		अगर (vi->cmd.cfg.cfg_func == VDA_CFG_GET_INIT) अणु
			काष्ठा atto_ioctl_vda_cfg_cmd *cfg = &vi->cmd.cfg;
			काष्ठा atto_vda_cfg_rsp *rsp = &rq->func_rsp.cfg_rsp;
			अक्षर buf[माप(cfg->data.init.fw_release) + 1];

			cfg->data_length =
				cpu_to_le32(माप(काष्ठा atto_vda_cfg_init));
			cfg->data.init.vda_version =
				le32_to_cpu(rsp->vda_version);
			cfg->data.init.fw_build = rsp->fw_build;

			snम_लिखो(buf, माप(buf), "%1.1u.%2.2u",
				 (पूर्णांक)LOBYTE(le16_to_cpu(rsp->fw_release)),
				 (पूर्णांक)HIBYTE(le16_to_cpu(rsp->fw_release)));

			स_नकल(&cfg->data.init.fw_release, buf,
			       माप(cfg->data.init.fw_release));

			अगर (LOWORD(LOBYTE(cfg->data.init.fw_build)) == 'A')
				cfg->data.init.fw_version =
					cfg->data.init.fw_build;
			अन्यथा
				cfg->data.init.fw_version =
					cfg->data.init.fw_release;
		पूर्ण अन्यथा अणु
			esas2r_nuxi_cfg_data(rq->vrq->cfg.sub_func,
					     &vi->cmd.cfg.data);
		पूर्ण

		अवरोध;

	हाल VDA_FUNC_CLI:

		vi->cmd.cli.cmd_rsp_len =
			le32_to_cpu(rq->func_rsp.cli_rsp.cmd_rsp_len);
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण
पूर्ण

/* Build a flash VDA request. */
व्योम esas2r_build_flash_req(काष्ठा esas2r_adapter *a,
			    काष्ठा esas2r_request *rq,
			    u8 sub_func,
			    u8 cksum,
			    u32 addr,
			    u32 length)
अणु
	काष्ठा atto_vda_flash_req *vrq = &rq->vrq->flash;

	clear_vda_request(rq);

	rq->vrq->scsi.function = VDA_FUNC_FLASH;

	अगर (sub_func == VDA_FLASH_BEGINW
	    || sub_func == VDA_FLASH_WRITE
	    || sub_func == VDA_FLASH_READ)
		vrq->sg_list_offset = (u8)दुरत्व(काष्ठा atto_vda_flash_req,
						   data.sge);

	vrq->length = cpu_to_le32(length);
	vrq->flash_addr = cpu_to_le32(addr);
	vrq->checksum = cksum;
	vrq->sub_func = sub_func;
पूर्ण

/* Build a VDA management request. */
व्योम esas2r_build_mgt_req(काष्ठा esas2r_adapter *a,
			  काष्ठा esas2r_request *rq,
			  u8 sub_func,
			  u8 scan_gen,
			  u16 dev_index,
			  u32 length,
			  व्योम *data)
अणु
	काष्ठा atto_vda_mgmt_req *vrq = &rq->vrq->mgt;

	clear_vda_request(rq);

	rq->vrq->scsi.function = VDA_FUNC_MGT;

	vrq->mgt_func = sub_func;
	vrq->scan_generation = scan_gen;
	vrq->dev_index = cpu_to_le16(dev_index);
	vrq->length = cpu_to_le32(length);

	अगर (vrq->length) अणु
		अगर (test_bit(AF_LEGACY_SGE_MODE, &a->flags)) अणु
			vrq->sg_list_offset = (u8)दुरत्व(
				काष्ठा atto_vda_mgmt_req, sge);

			vrq->sge[0].length = cpu_to_le32(SGE_LAST | length);
			vrq->sge[0].address = cpu_to_le64(
				rq->vrq_md->phys_addr +
				माप(जोड़ atto_vda_req));
		पूर्ण अन्यथा अणु
			vrq->sg_list_offset = (u8)दुरत्व(
				काष्ठा atto_vda_mgmt_req, prde);

			vrq->prde[0].ctl_len = cpu_to_le32(length);
			vrq->prde[0].address = cpu_to_le64(
				rq->vrq_md->phys_addr +
				माप(जोड़ atto_vda_req));
		पूर्ण
	पूर्ण

	अगर (data) अणु
		esas2r_nuxi_mgt_data(sub_func, data);

		स_नकल(&rq->vda_rsp_data->mgt_data.data.bytes[0], data,
		       length);
	पूर्ण
पूर्ण

/* Build a VDA asyncronous event (AE) request. */
व्योम esas2r_build_ae_req(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq)
अणु
	काष्ठा atto_vda_ae_req *vrq = &rq->vrq->ae;

	clear_vda_request(rq);

	rq->vrq->scsi.function = VDA_FUNC_AE;

	vrq->length = cpu_to_le32(माप(काष्ठा atto_vda_ae_data));

	अगर (test_bit(AF_LEGACY_SGE_MODE, &a->flags)) अणु
		vrq->sg_list_offset =
			(u8)दुरत्व(काष्ठा atto_vda_ae_req, sge);
		vrq->sge[0].length = cpu_to_le32(SGE_LAST | vrq->length);
		vrq->sge[0].address = cpu_to_le64(
			rq->vrq_md->phys_addr +
			माप(जोड़ atto_vda_req));
	पूर्ण अन्यथा अणु
		vrq->sg_list_offset = (u8)दुरत्व(काष्ठा atto_vda_ae_req,
						   prde);
		vrq->prde[0].ctl_len = cpu_to_le32(vrq->length);
		vrq->prde[0].address = cpu_to_le64(
			rq->vrq_md->phys_addr +
			माप(जोड़ atto_vda_req));
	पूर्ण
पूर्ण

/* Build a VDA CLI request. */
व्योम esas2r_build_cli_req(काष्ठा esas2r_adapter *a,
			  काष्ठा esas2r_request *rq,
			  u32 length,
			  u32 cmd_rsp_len)
अणु
	काष्ठा atto_vda_cli_req *vrq = &rq->vrq->cli;

	clear_vda_request(rq);

	rq->vrq->scsi.function = VDA_FUNC_CLI;

	vrq->length = cpu_to_le32(length);
	vrq->cmd_rsp_len = cpu_to_le32(cmd_rsp_len);
	vrq->sg_list_offset = (u8)दुरत्व(काष्ठा atto_vda_cli_req, sge);
पूर्ण

/* Build a VDA IOCTL request. */
व्योम esas2r_build_ioctl_req(काष्ठा esas2r_adapter *a,
			    काष्ठा esas2r_request *rq,
			    u32 length,
			    u8 sub_func)
अणु
	काष्ठा atto_vda_ioctl_req *vrq = &rq->vrq->ioctl;

	clear_vda_request(rq);

	rq->vrq->scsi.function = VDA_FUNC_IOCTL;

	vrq->length = cpu_to_le32(length);
	vrq->sub_func = sub_func;
	vrq->sg_list_offset = (u8)दुरत्व(काष्ठा atto_vda_ioctl_req, sge);
पूर्ण

/* Build a VDA configuration request. */
व्योम esas2r_build_cfg_req(काष्ठा esas2r_adapter *a,
			  काष्ठा esas2r_request *rq,
			  u8 sub_func,
			  u32 length,
			  व्योम *data)
अणु
	काष्ठा atto_vda_cfg_req *vrq = &rq->vrq->cfg;

	clear_vda_request(rq);

	rq->vrq->scsi.function = VDA_FUNC_CFG;

	vrq->sub_func = sub_func;
	vrq->length = cpu_to_le32(length);

	अगर (data) अणु
		esas2r_nuxi_cfg_data(sub_func, data);

		स_नकल(&vrq->data, data, length);
	पूर्ण
पूर्ण

अटल व्योम clear_vda_request(काष्ठा esas2r_request *rq)
अणु
	u32 handle = rq->vrq->scsi.handle;

	स_रखो(rq->vrq, 0, माप(*rq->vrq));

	rq->vrq->scsi.handle = handle;

	rq->req_stat = RS_PENDING;

	/* since the data buffer is separate clear that too */

	स_रखो(rq->data_buf, 0, ESAS2R_DATA_BUF_LEN);

	/*
	 * Setup next and prev poपूर्णांकer in हाल the request is not going through
	 * esas2r_start_request().
	 */

	INIT_LIST_HEAD(&rq->req_list);
पूर्ण
