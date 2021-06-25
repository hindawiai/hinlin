<शैली गुरु>

/*
 *  linux/drivers/scsi/esas2r/esas2r_flash.c
 *      For use with ATTO ExpressSAS R6xx SAS/SATA RAID controllers
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * NO WARRANTY
 * THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 * LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 * solely responsible क्रम determining the appropriateness of using and
 * distributing the Program and assumes all risks associated with its
 * exercise of rights under this Agreement, including but not limited to
 * the risks and costs of program errors, damage to or loss of data,
 * programs or equipment, and unavailability or पूर्णांकerruption of operations.
 *
 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#समावेश "esas2r.h"

/* local macro defs */
#घोषणा esas2r_nvramcalc_cksum(n)     \
	(esas2r_calc_byte_cksum((u8 *)(n), माप(काष्ठा esas2r_sas_nvram), \
				SASNVR_CKSUM_SEED))
#घोषणा esas2r_nvramcalc_xor_cksum(n)  \
	(esas2r_calc_byte_xor_cksum((u8 *)(n), \
				    माप(काष्ठा esas2r_sas_nvram), 0))

#घोषणा ESAS2R_FS_DRVR_VER 2

अटल काष्ठा esas2r_sas_nvram शेष_sas_nvram = अणु
	अणु 'E',	'S',  'A',  'S'			     पूर्ण, /* signature          */
	SASNVR_VERSION,                                 /* version            */
	0,                                              /* checksum           */
	31,                                             /* max_lun_क्रम_target */
	SASNVR_PCILAT_MAX,                              /* pci_latency        */
	SASNVR1_BOOT_DRVR,                              /* options1           */
	SASNVR2_HEARTBEAT   | SASNVR2_SINGLE_BUS        /* options2           */
	| SASNVR2_SW_MUX_CTRL,
	SASNVR_COAL_DIS,                                /* पूर्णांक_coalescing     */
	SASNVR_CMDTHR_NONE,                             /* cmd_throttle       */
	3,                                              /* dev_रुको_समय      */
	1,                                              /* dev_रुको_count     */
	0,                                              /* spin_up_delay      */
	0,                                              /* ssp_align_rate     */
	अणु 0x50, 0x01, 0x08, 0x60,                       /* sas_addr           */
	  0x00, 0x00, 0x00, 0x00 पूर्ण,
	अणु SASNVR_SPEED_AUTO पूर्ण,                          /* phy_speed          */
	अणु SASNVR_MUX_DISABLED पूर्ण,                        /* SAS multiplexing   */
	अणु 0 पूर्ण,                                          /* phy_flags          */
	SASNVR_SORT_SAS_ADDR,                           /* sort_type          */
	3,                                              /* dpm_reqcmd_lmt     */
	3,                                              /* dpm_stndby_समय    */
	0,                                              /* dpm_active_समय    */
	अणु 0 पूर्ण,                                          /* phy_target_id      */
	SASNVR_VSMH_DISABLED,                           /* virt_ses_mode      */
	SASNVR_RWM_DEFAULT,                             /* पढ़ो_ग_लिखो_mode    */
	0,                                              /* link करोwn समयout  */
	अणु 0 पूर्ण                                           /* reserved           */
पूर्ण;

अटल u8 cmd_to_fls_func[] = अणु
	0xFF,
	VDA_FLASH_READ,
	VDA_FLASH_BEGINW,
	VDA_FLASH_WRITE,
	VDA_FLASH_COMMIT,
	VDA_FLASH_CANCEL
पूर्ण;

अटल u8 esas2r_calc_byte_xor_cksum(u8 *addr, u32 len, u8 seed)
अणु
	u32 cksum = seed;
	u8 *p = (u8 *)&cksum;

	जबतक (len) अणु
		अगर (((uपूर्णांकptr_t)addr & 3) == 0)
			अवरोध;

		cksum = cksum ^ *addr;
		addr++;
		len--;
	पूर्ण
	जबतक (len >= माप(u32)) अणु
		cksum = cksum ^ *(u32 *)addr;
		addr += 4;
		len -= 4;
	पूर्ण
	जबतक (len--) अणु
		cksum = cksum ^ *addr;
		addr++;
	पूर्ण
	वापस p[0] ^ p[1] ^ p[2] ^ p[3];
पूर्ण

अटल u8 esas2r_calc_byte_cksum(व्योम *addr, u32 len, u8 seed)
अणु
	u8 *p = (u8 *)addr;
	u8 cksum = seed;

	जबतक (len--)
		cksum = cksum + p[len];
	वापस cksum;
पूर्ण

/* Interrupt callback to process FM API ग_लिखो requests. */
अटल व्योम esas2r_fmapi_callback(काष्ठा esas2r_adapter *a,
				  काष्ठा esas2r_request *rq)
अणु
	काष्ठा atto_vda_flash_req *vrq = &rq->vrq->flash;
	काष्ठा esas2r_flash_context *fc =
		(काष्ठा esas2r_flash_context *)rq->पूर्णांकerrupt_cx;

	अगर (rq->req_stat == RS_SUCCESS) अणु
		/* Last request was successful.  See what to करो now. */
		चयन (vrq->sub_func) अणु
		हाल VDA_FLASH_BEGINW:
			अगर (fc->sgc.cur_offset == शून्य)
				जाओ commit;

			vrq->sub_func = VDA_FLASH_WRITE;
			rq->req_stat = RS_PENDING;
			अवरोध;

		हाल VDA_FLASH_WRITE:
commit:
			vrq->sub_func = VDA_FLASH_COMMIT;
			rq->req_stat = RS_PENDING;
			rq->पूर्णांकerrupt_cb = fc->पूर्णांकerrupt_cb;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rq->req_stat != RS_PENDING)
		/*
		 * All करोne. call the real callback to complete the FM API
		 * request.  We should only get here अगर a BEGINW or WRITE
		 * operation failed.
		 */
		(*fc->पूर्णांकerrupt_cb)(a, rq);
पूर्ण

/*
 * Build a flash request based on the flash context.  The request status
 * is filled in on an error.
 */
अटल व्योम build_flash_msg(काष्ठा esas2r_adapter *a,
			    काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_flash_context *fc =
		(काष्ठा esas2r_flash_context *)rq->पूर्णांकerrupt_cx;
	काष्ठा esas2r_sg_context *sgc = &fc->sgc;
	u8 cksum = 0;

	/* calculate the checksum */
	अगर (fc->func == VDA_FLASH_BEGINW) अणु
		अगर (sgc->cur_offset)
			cksum = esas2r_calc_byte_xor_cksum(sgc->cur_offset,
							   sgc->length,
							   0);
		rq->पूर्णांकerrupt_cb = esas2r_fmapi_callback;
	पूर्ण अन्यथा अणु
		rq->पूर्णांकerrupt_cb = fc->पूर्णांकerrupt_cb;
	पूर्ण
	esas2r_build_flash_req(a,
			       rq,
			       fc->func,
			       cksum,
			       fc->flsh_addr,
			       sgc->length);

	esas2r_rq_मुक्त_sg_lists(rq, a);

	/*
	 * remember the length we asked क्रम.  we have to keep track of
	 * the current amount करोne so we know how much to compare when
	 * करोing the verअगरication phase.
	 */
	fc->curr_len = fc->sgc.length;

	अगर (sgc->cur_offset) अणु
		/* setup the S/G context to build the S/G table  */
		esas2r_sgc_init(sgc, a, rq, &rq->vrq->flash.data.sge[0]);

		अगर (!esas2r_build_sg_list(a, rq, sgc)) अणु
			rq->req_stat = RS_BUSY;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		fc->sgc.length = 0;
	पूर्ण

	/* update the flsh_addr to the next one to ग_लिखो to  */
	fc->flsh_addr += fc->curr_len;
पूर्ण

/* determine the method to process the flash request */
अटल bool load_image(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq)
अणु
	/*
	 * assume we have more to करो.  अगर we वापस with the status set to
	 * RS_PENDING, FM API tasks will जारी.
	 */
	rq->req_stat = RS_PENDING;
	अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
		/* not suppported क्रम now */;
	अन्यथा
		build_flash_msg(a, rq);

	वापस rq->req_stat == RS_PENDING;
पूर्ण

/*  boot image fixer uppers called beक्रमe करोwnloading the image. */
अटल व्योम fix_bios(काष्ठा esas2r_adapter *a, काष्ठा esas2r_flash_img *fi)
अणु
	काष्ठा esas2r_component_header *ch = &fi->cmp_hdr[CH_IT_BIOS];
	काष्ठा esas2r_pc_image *pi;
	काष्ठा esas2r_boot_header *bh;

	pi = (काष्ठा esas2r_pc_image *)((u8 *)fi + ch->image_offset);
	bh =
		(काष्ठा esas2r_boot_header *)((u8 *)pi +
					      le16_to_cpu(pi->header_offset));
	bh->device_id = cpu_to_le16(a->pcid->device);

	/* Recalculate the checksum in the PNP header अगर there  */
	अगर (pi->pnp_offset) अणु
		u8 *pnp_header_bytes =
			((u8 *)pi + le16_to_cpu(pi->pnp_offset));

		/* Identअगरier - dword that starts at byte 10 */
		*((u32 *)&pnp_header_bytes[10]) =
			cpu_to_le32(MAKEDWORD(a->pcid->subप्रणाली_venकरोr,
					      a->pcid->subप्रणाली_device));

		/* Checksum - byte 9 */
		pnp_header_bytes[9] -= esas2r_calc_byte_cksum(pnp_header_bytes,
							      32, 0);
	पूर्ण

	/* Recalculate the checksum needed by the PC */
	pi->checksum = pi->checksum -
		       esas2r_calc_byte_cksum((u8 *)pi, ch->length, 0);
पूर्ण

अटल व्योम fix_efi(काष्ठा esas2r_adapter *a, काष्ठा esas2r_flash_img *fi)
अणु
	काष्ठा esas2r_component_header *ch = &fi->cmp_hdr[CH_IT_EFI];
	u32 len = ch->length;
	u32 offset = ch->image_offset;
	काष्ठा esas2r_efi_image *ei;
	काष्ठा esas2r_boot_header *bh;

	जबतक (len) अणु
		u32 thislen;

		ei = (काष्ठा esas2r_efi_image *)((u8 *)fi + offset);
		bh = (काष्ठा esas2r_boot_header *)((u8 *)ei +
						   le16_to_cpu(
							   ei->header_offset));
		bh->device_id = cpu_to_le16(a->pcid->device);
		thislen = (u32)le16_to_cpu(bh->image_length) * 512;

		अगर (thislen > len)
			अवरोध;

		len -= thislen;
		offset += thislen;
	पूर्ण
पूर्ण

/* Complete a FM API request with the specअगरied status. */
अटल bool complete_fmapi_req(काष्ठा esas2r_adapter *a,
			       काष्ठा esas2r_request *rq, u8 fi_stat)
अणु
	काष्ठा esas2r_flash_context *fc =
		(काष्ठा esas2r_flash_context *)rq->पूर्णांकerrupt_cx;
	काष्ठा esas2r_flash_img *fi = fc->fi;

	fi->status = fi_stat;
	fi->driver_error = rq->req_stat;
	rq->पूर्णांकerrupt_cb = शून्य;
	rq->req_stat = RS_SUCCESS;

	अगर (fi_stat != FI_STAT_IMG_VER)
		स_रखो(fc->scratch, 0, FM_BUF_SZ);

	esas2r_enable_heartbeat(a);
	clear_bit(AF_FLASH_LOCK, &a->flags);
	वापस false;
पूर्ण

/* Process each phase of the flash करोwnload process. */
अटल व्योम fw_करोwnload_proc(काष्ठा esas2r_adapter *a,
			     काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_flash_context *fc =
		(काष्ठा esas2r_flash_context *)rq->पूर्णांकerrupt_cx;
	काष्ठा esas2r_flash_img *fi = fc->fi;
	काष्ठा esas2r_component_header *ch;
	u32 len;
	u8 *p, *q;

	/* If the previous operation failed, just वापस. */
	अगर (rq->req_stat != RS_SUCCESS)
		जाओ error;

	/*
	 * If an upload just completed and the compare length is non-zero,
	 * then we just पढ़ो back part of the image we just wrote.  verअगरy the
	 * section and जारी पढ़ोing until the entire image is verअगरied.
	 */
	अगर (fc->func == VDA_FLASH_READ
	    && fc->cmp_len) अणु
		ch = &fi->cmp_hdr[fc->comp_typ];

		p = fc->scratch;
		q = (u8 *)fi                    /* start of the whole gob     */
		    + ch->image_offset          /* start of the current image */
		    + ch->length                /* end of the current image   */
		    - fc->cmp_len;              /* where we are now           */

		/*
		 * NOTE - curr_len is the exact count of bytes क्रम the पढ़ो
		 *        even when the end is पढ़ो and its not a full buffer
		 */
		क्रम (len = fc->curr_len; len; len--)
			अगर (*p++ != *q++)
				जाओ error;

		fc->cmp_len -= fc->curr_len; /* # left to compare    */

		/* Update fc and determine the length क्रम the next upload */
		अगर (fc->cmp_len > FM_BUF_SZ)
			fc->sgc.length = FM_BUF_SZ;
		अन्यथा
			fc->sgc.length = fc->cmp_len;

		fc->sgc.cur_offset = fc->sgc_offset +
				     ((u8 *)fc->scratch - (u8 *)fi);
	पूर्ण

	/*
	 * This code uses a 'while' statement since the next component may
	 * have a length = zero.  This can happen since some components are
	 * not required.  At the end of this 'while' we set up the length
	 * क्रम the next request and thereक्रमe sgc.length can be = 0.
	 */
	जबतक (fc->sgc.length == 0) अणु
		ch = &fi->cmp_hdr[fc->comp_typ];

		चयन (fc->task) अणु
		हाल FMTSK_ERASE_BOOT:
			/* the BIOS image is written next */
			ch = &fi->cmp_hdr[CH_IT_BIOS];
			अगर (ch->length == 0)
				जाओ no_bios;

			fc->task = FMTSK_WRTBIOS;
			fc->func = VDA_FLASH_BEGINW;
			fc->comp_typ = CH_IT_BIOS;
			fc->flsh_addr = FLS_OFFSET_BOOT;
			fc->sgc.length = ch->length;
			fc->sgc.cur_offset = fc->sgc_offset +
					     ch->image_offset;
			अवरोध;

		हाल FMTSK_WRTBIOS:
			/*
			 * The BIOS image has been written - पढ़ो it and
			 * verअगरy it
			 */
			fc->task = FMTSK_READBIOS;
			fc->func = VDA_FLASH_READ;
			fc->flsh_addr = FLS_OFFSET_BOOT;
			fc->cmp_len = ch->length;
			fc->sgc.length = FM_BUF_SZ;
			fc->sgc.cur_offset = fc->sgc_offset
					     + ((u8 *)fc->scratch -
						(u8 *)fi);
			अवरोध;

		हाल FMTSK_READBIOS:
no_bios:
			/*
			 * Mark the component header status क्रम the image
			 * completed
			 */
			ch->status = CH_STAT_SUCCESS;

			/* The MAC image is written next */
			ch = &fi->cmp_hdr[CH_IT_MAC];
			अगर (ch->length == 0)
				जाओ no_mac;

			fc->task = FMTSK_WRTMAC;
			fc->func = VDA_FLASH_BEGINW;
			fc->comp_typ = CH_IT_MAC;
			fc->flsh_addr = FLS_OFFSET_BOOT
					+ fi->cmp_hdr[CH_IT_BIOS].length;
			fc->sgc.length = ch->length;
			fc->sgc.cur_offset = fc->sgc_offset +
					     ch->image_offset;
			अवरोध;

		हाल FMTSK_WRTMAC:
			/* The MAC image has been written - पढ़ो and verअगरy */
			fc->task = FMTSK_READMAC;
			fc->func = VDA_FLASH_READ;
			fc->flsh_addr -= ch->length;
			fc->cmp_len = ch->length;
			fc->sgc.length = FM_BUF_SZ;
			fc->sgc.cur_offset = fc->sgc_offset
					     + ((u8 *)fc->scratch -
						(u8 *)fi);
			अवरोध;

		हाल FMTSK_READMAC:
no_mac:
			/*
			 * Mark the component header status क्रम the image
			 * completed
			 */
			ch->status = CH_STAT_SUCCESS;

			/* The EFI image is written next */
			ch = &fi->cmp_hdr[CH_IT_EFI];
			अगर (ch->length == 0)
				जाओ no_efi;

			fc->task = FMTSK_WRTEFI;
			fc->func = VDA_FLASH_BEGINW;
			fc->comp_typ = CH_IT_EFI;
			fc->flsh_addr = FLS_OFFSET_BOOT
					+ fi->cmp_hdr[CH_IT_BIOS].length
					+ fi->cmp_hdr[CH_IT_MAC].length;
			fc->sgc.length = ch->length;
			fc->sgc.cur_offset = fc->sgc_offset +
					     ch->image_offset;
			अवरोध;

		हाल FMTSK_WRTEFI:
			/* The EFI image has been written - पढ़ो and verअगरy */
			fc->task = FMTSK_READEFI;
			fc->func = VDA_FLASH_READ;
			fc->flsh_addr -= ch->length;
			fc->cmp_len = ch->length;
			fc->sgc.length = FM_BUF_SZ;
			fc->sgc.cur_offset = fc->sgc_offset
					     + ((u8 *)fc->scratch -
						(u8 *)fi);
			अवरोध;

		हाल FMTSK_READEFI:
no_efi:
			/*
			 * Mark the component header status क्रम the image
			 * completed
			 */
			ch->status = CH_STAT_SUCCESS;

			/* The CFG image is written next */
			ch = &fi->cmp_hdr[CH_IT_CFG];

			अगर (ch->length == 0)
				जाओ no_cfg;
			fc->task = FMTSK_WRTCFG;
			fc->func = VDA_FLASH_BEGINW;
			fc->comp_typ = CH_IT_CFG;
			fc->flsh_addr = FLS_OFFSET_CPYR - ch->length;
			fc->sgc.length = ch->length;
			fc->sgc.cur_offset = fc->sgc_offset +
					     ch->image_offset;
			अवरोध;

		हाल FMTSK_WRTCFG:
			/* The CFG image has been written - पढ़ो and verअगरy */
			fc->task = FMTSK_READCFG;
			fc->func = VDA_FLASH_READ;
			fc->flsh_addr = FLS_OFFSET_CPYR - ch->length;
			fc->cmp_len = ch->length;
			fc->sgc.length = FM_BUF_SZ;
			fc->sgc.cur_offset = fc->sgc_offset
					     + ((u8 *)fc->scratch -
						(u8 *)fi);
			अवरोध;

		हाल FMTSK_READCFG:
no_cfg:
			/*
			 * Mark the component header status क्रम the image
			 * completed
			 */
			ch->status = CH_STAT_SUCCESS;

			/*
			 * The करोwnload is complete.  If in degraded mode,
			 * attempt a chip reset.
			 */
			अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
				esas2r_local_reset_adapter(a);

			a->flash_ver = fi->cmp_hdr[CH_IT_BIOS].version;
			esas2r_prपूर्णांक_flash_rev(a);

			/* Update the type of boot image on the card */
			स_नकल(a->image_type, fi->rel_version,
			       माप(fi->rel_version));
			complete_fmapi_req(a, rq, FI_STAT_SUCCESS);
			वापस;
		पूर्ण

		/* If verअगरying, करोn't try reading more than what's there */
		अगर (fc->func == VDA_FLASH_READ
		    && fc->sgc.length > fc->cmp_len)
			fc->sgc.length = fc->cmp_len;
	पूर्ण

	/* Build the request to perक्रमm the next action */
	अगर (!load_image(a, rq)) अणु
error:
		अगर (fc->comp_typ < fi->num_comps) अणु
			ch = &fi->cmp_hdr[fc->comp_typ];
			ch->status = CH_STAT_FAILED;
		पूर्ण

		complete_fmapi_req(a, rq, FI_STAT_FAILED);
	पूर्ण
पूर्ण

/* Determine the flash image adaptyp क्रम this adapter */
अटल u8 get_fi_adap_type(काष्ठा esas2r_adapter *a)
अणु
	u8 type;

	/* use the device ID to get the correct adap_typ क्रम this HBA */
	चयन (a->pcid->device) अणु
	हाल ATTO_DID_INTEL_IOP348:
		type = FI_AT_SUN_LAKE;
		अवरोध;

	हाल ATTO_DID_MV_88RC9580:
	हाल ATTO_DID_MV_88RC9580TS:
	हाल ATTO_DID_MV_88RC9580TSE:
	हाल ATTO_DID_MV_88RC9580TL:
		type = FI_AT_MV_9580;
		अवरोध;

	शेष:
		type = FI_AT_UNKNWN;
		अवरोध;
	पूर्ण

	वापस type;
पूर्ण

/* Size of config + copyright + flash_ver images, 0 क्रम failure. */
अटल u32 chk_cfg(u8 *cfg, u32 length, u32 *flash_ver)
अणु
	u16 *pw = (u16 *)cfg - 1;
	u32 sz = 0;
	u32 len = length;

	अगर (len == 0)
		len = FM_BUF_SZ;

	अगर (flash_ver)
		*flash_ver = 0;

	जबतक (true) अणु
		u16 type;
		u16 size;

		type = le16_to_cpu(*pw--);
		size = le16_to_cpu(*pw--);

		अगर (type != FBT_CPYR
		    && type != FBT_SETUP
		    && type != FBT_FLASH_VER)
			अवरोध;

		अगर (type == FBT_FLASH_VER
		    && flash_ver)
			*flash_ver = le32_to_cpu(*(u32 *)(pw - 1));

		sz += size + (2 * माप(u16));
		pw -= size / माप(u16);

		अगर (sz > len - (2 * माप(u16)))
			अवरोध;
	पूर्ण

	/* See अगर we are comparing the size to the specअगरied length */
	अगर (length && sz != length)
		वापस 0;

	वापस sz;
पूर्ण

/* Verअगरy that the boot image is valid */
अटल u8 chk_boot(u8 *boot_img, u32 length)
अणु
	काष्ठा esas2r_boot_image *bi = (काष्ठा esas2r_boot_image *)boot_img;
	u16 hdroffset = le16_to_cpu(bi->header_offset);
	काष्ठा esas2r_boot_header *bh;

	अगर (bi->signature != le16_to_cpu(0xaa55)
	    || (दीर्घ)hdroffset >
	    (दीर्घ)(65536L - माप(काष्ठा esas2r_boot_header))
	    || (hdroffset & 3)
	    || (hdroffset < माप(काष्ठा esas2r_boot_image))
	    || ((u32)hdroffset + माप(काष्ठा esas2r_boot_header) > length))
		वापस 0xff;

	bh = (काष्ठा esas2r_boot_header *)((अक्षर *)bi + hdroffset);

	अगर (bh->signature[0] != 'P'
	    || bh->signature[1] != 'C'
	    || bh->signature[2] != 'I'
	    || bh->signature[3] != 'R'
	    || le16_to_cpu(bh->काष्ठा_length) <
	    (u16)माप(काष्ठा esas2r_boot_header)
	    || bh->class_code[2] != 0x01
	    || bh->class_code[1] != 0x04
	    || bh->class_code[0] != 0x00
	    || (bh->code_type != CODE_TYPE_PC
		&& bh->code_type != CODE_TYPE_OPEN
		&& bh->code_type != CODE_TYPE_EFI))
		वापस 0xff;

	वापस bh->code_type;
पूर्ण

/* The sum of all the WORDS of the image */
अटल u16 calc_fi_checksum(काष्ठा esas2r_flash_context *fc)
अणु
	काष्ठा esas2r_flash_img *fi = fc->fi;
	u16 cksum;
	u32 len;
	u16 *pw;

	क्रम (len = (fi->length - fc->fi_hdr_len) / 2,
	     pw = (u16 *)((u8 *)fi + fc->fi_hdr_len),
	     cksum = 0;
	     len;
	     len--, pw++)
		cksum = cksum + le16_to_cpu(*pw);

	वापस cksum;
पूर्ण

/*
 * Verअगरy the flash image काष्ठाure.  The following verअगरications will
 * be perक्रमmed:
 *              1)  verअगरy the fi_version is correct
 *              2)  verअगरy the checksum of the entire image.
 *              3)  validate the adap_typ, action and length fields.
 *              4)  validate each component header. check the img_type and
 *                  length fields
 *              5)  validate each component image.  validate signatures and
 *                  local checksums
 */
अटल bool verअगरy_fi(काष्ठा esas2r_adapter *a,
		      काष्ठा esas2r_flash_context *fc)
अणु
	काष्ठा esas2r_flash_img *fi = fc->fi;
	u8 type;
	bool imgerr;
	u16 i;
	u32 len;
	काष्ठा esas2r_component_header *ch;

	/* Verअगरy the length - length must even since we करो a word checksum */
	len = fi->length;

	अगर ((len & 1)
	    || len < fc->fi_hdr_len) अणु
		fi->status = FI_STAT_LENGTH;
		वापस false;
	पूर्ण

	/* Get adapter type and verअगरy type in flash image */
	type = get_fi_adap_type(a);
	अगर ((type == FI_AT_UNKNWN) || (fi->adap_typ != type)) अणु
		fi->status = FI_STAT_ADAPTYP;
		वापस false;
	पूर्ण

	/*
	 * Loop through each component and verअगरy the img_type and length
	 * fields.  Keep a running count of the sizes sooze we can verअगरy total
	 * size to additive size.
	 */
	imgerr = false;

	क्रम (i = 0, len = 0, ch = fi->cmp_hdr;
	     i < fi->num_comps;
	     i++, ch++) अणु
		bool cmperr = false;

		/*
		 * Verअगरy that the component header has the same index as the
		 * image type.  The headers must be ordered correctly
		 */
		अगर (i != ch->img_type) अणु
			imgerr = true;
			ch->status = CH_STAT_INVALID;
			जारी;
		पूर्ण

		चयन (ch->img_type) अणु
		हाल CH_IT_BIOS:
			type = CODE_TYPE_PC;
			अवरोध;

		हाल CH_IT_MAC:
			type = CODE_TYPE_OPEN;
			अवरोध;

		हाल CH_IT_EFI:
			type = CODE_TYPE_EFI;
			अवरोध;
		पूर्ण

		चयन (ch->img_type) अणु
		हाल CH_IT_FW:
		हाल CH_IT_NVR:
			अवरोध;

		हाल CH_IT_BIOS:
		हाल CH_IT_MAC:
		हाल CH_IT_EFI:
			अगर (ch->length & 0x1ff)
				cmperr = true;

			/* Test अगर component image is present  */
			अगर (ch->length == 0)
				अवरोध;

			/* Image is present - verअगरy the image */
			अगर (chk_boot((u8 *)fi + ch->image_offset, ch->length)
			    != type)
				cmperr = true;

			अवरोध;

		हाल CH_IT_CFG:

			/* Test अगर component image is present */
			अगर (ch->length == 0) अणु
				cmperr = true;
				अवरोध;
			पूर्ण

			/* Image is present - verअगरy the image */
			अगर (!chk_cfg((u8 *)fi + ch->image_offset + ch->length,
				     ch->length, शून्य))
				cmperr = true;

			अवरोध;

		शेष:

			fi->status = FI_STAT_UNKNOWN;
			वापस false;
		पूर्ण

		अगर (cmperr) अणु
			imgerr = true;
			ch->status = CH_STAT_INVALID;
		पूर्ण अन्यथा अणु
			ch->status = CH_STAT_PENDING;
			len += ch->length;
		पूर्ण
	पूर्ण

	अगर (imgerr) अणु
		fi->status = FI_STAT_MISSING;
		वापस false;
	पूर्ण

	/* Compare fi->length to the sum of ch->length fields */
	अगर (len != fi->length - fc->fi_hdr_len) अणु
		fi->status = FI_STAT_LENGTH;
		वापस false;
	पूर्ण

	/* Compute the checksum - it should come out zero */
	अगर (fi->checksum != calc_fi_checksum(fc)) अणु
		fi->status = FI_STAT_CHKSUM;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Fill in the FS IOCTL response data from a completed request. */
अटल व्योम esas2r_complete_fs_ioctl(काष्ठा esas2r_adapter *a,
				     काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_ioctl_fs *fs =
		(काष्ठा esas2r_ioctl_fs *)rq->पूर्णांकerrupt_cx;

	अगर (rq->vrq->flash.sub_func == VDA_FLASH_COMMIT)
		esas2r_enable_heartbeat(a);

	fs->driver_error = rq->req_stat;

	अगर (fs->driver_error == RS_SUCCESS)
		fs->status = ATTO_STS_SUCCESS;
	अन्यथा
		fs->status = ATTO_STS_FAILED;
पूर्ण

/* Prepare an FS IOCTL request to be sent to the firmware. */
bool esas2r_process_fs_ioctl(काष्ठा esas2r_adapter *a,
			     काष्ठा esas2r_ioctl_fs *fs,
			     काष्ठा esas2r_request *rq,
			     काष्ठा esas2r_sg_context *sgc)
अणु
	u8 cmdcnt = (u8)ARRAY_SIZE(cmd_to_fls_func);
	काष्ठा esas2r_ioctlfs_command *fsc = &fs->command;
	u8 func = 0;
	u32 datalen;

	fs->status = ATTO_STS_FAILED;
	fs->driver_error = RS_PENDING;

	अगर (fs->version > ESAS2R_FS_VER) अणु
		fs->status = ATTO_STS_INV_VERSION;
		वापस false;
	पूर्ण

	अगर (fsc->command >= cmdcnt) अणु
		fs->status = ATTO_STS_INV_FUNC;
		वापस false;
	पूर्ण

	func = cmd_to_fls_func[fsc->command];
	अगर (func == 0xFF) अणु
		fs->status = ATTO_STS_INV_FUNC;
		वापस false;
	पूर्ण

	अगर (fsc->command != ESAS2R_FS_CMD_CANCEL) अणु
		अगर ((a->pcid->device != ATTO_DID_MV_88RC9580
		     || fs->adap_type != ESAS2R_FS_AT_ESASRAID2)
		    && (a->pcid->device != ATTO_DID_MV_88RC9580TS
			|| fs->adap_type != ESAS2R_FS_AT_TSSASRAID2)
		    && (a->pcid->device != ATTO_DID_MV_88RC9580TSE
			|| fs->adap_type != ESAS2R_FS_AT_TSSASRAID2E)
		    && (a->pcid->device != ATTO_DID_MV_88RC9580TL
			|| fs->adap_type != ESAS2R_FS_AT_TLSASHBA)) अणु
			fs->status = ATTO_STS_INV_ADAPTER;
			वापस false;
		पूर्ण

		अगर (fs->driver_ver > ESAS2R_FS_DRVR_VER) अणु
			fs->status = ATTO_STS_INV_DRVR_VER;
			वापस false;
		पूर्ण
	पूर्ण

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags)) अणु
		fs->status = ATTO_STS_DEGRADED;
		वापस false;
	पूर्ण

	rq->पूर्णांकerrupt_cb = esas2r_complete_fs_ioctl;
	rq->पूर्णांकerrupt_cx = fs;
	datalen = le32_to_cpu(fsc->length);
	esas2r_build_flash_req(a,
			       rq,
			       func,
			       fsc->checksum,
			       le32_to_cpu(fsc->flash_addr),
			       datalen);

	अगर (func == VDA_FLASH_WRITE
	    || func == VDA_FLASH_READ) अणु
		अगर (datalen == 0) अणु
			fs->status = ATTO_STS_INV_FUNC;
			वापस false;
		पूर्ण

		esas2r_sgc_init(sgc, a, rq, rq->vrq->flash.data.sge);
		sgc->length = datalen;

		अगर (!esas2r_build_sg_list(a, rq, sgc)) अणु
			fs->status = ATTO_STS_OUT_OF_RSRC;
			वापस false;
		पूर्ण
	पूर्ण

	अगर (func == VDA_FLASH_COMMIT)
		esas2r_disable_heartbeat(a);

	esas2r_start_request(a, rq);

	वापस true;
पूर्ण

अटल bool esas2r_flash_access(काष्ठा esas2r_adapter *a, u32 function)
अणु
	u32 startसमय;
	u32 समयout;
	u32 पूर्णांकstat;
	u32 करोorbell;

	/* Disable chip पूर्णांकerrupts aजबतक */
	अगर (function == DRBL_FLASH_REQ)
		esas2r_disable_chip_पूर्णांकerrupts(a);

	/* Issue the request to the firmware */
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_IN, function);

	/* Now रुको क्रम the firmware to process it */
	startसमय = jअगरfies_to_msecs(jअगरfies);

	अगर (test_bit(AF_CHPRST_PENDING, &a->flags) ||
	    test_bit(AF_DISC_PENDING, &a->flags))
		समयout = 40000;
	अन्यथा
		समयout = 5000;

	जबतक (true) अणु
		पूर्णांकstat = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_INT_STATUS_OUT);

		अगर (पूर्णांकstat & MU_INTSTAT_DRBL) अणु
			/* Got a करोorbell पूर्णांकerrupt.  Check क्रम the function */
			करोorbell =
				esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
			esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_OUT,
						    करोorbell);
			अगर (करोorbell & function)
				अवरोध;
		पूर्ण

		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

		अगर ((jअगरfies_to_msecs(jअगरfies) - startसमय) > समयout) अणु
			/*
			 * Iimeout.  If we were requesting flash access,
			 * indicate we are करोne so the firmware knows we gave
			 * up.  If this was a REQ, we also need to re-enable
			 * chip पूर्णांकerrupts.
			 */
			अगर (function == DRBL_FLASH_REQ) अणु
				esas2r_hdebug("flash access timeout");
				esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_IN,
							    DRBL_FLASH_DONE);
				esas2r_enable_chip_पूर्णांकerrupts(a);
			पूर्ण अन्यथा अणु
				esas2r_hdebug("flash release timeout");
			पूर्ण

			वापस false;
		पूर्ण
	पूर्ण

	/* अगर we're करोne, re-enable chip पूर्णांकerrupts */
	अगर (function == DRBL_FLASH_DONE)
		esas2r_enable_chip_पूर्णांकerrupts(a);

	वापस true;
पूर्ण

#घोषणा WINDOW_SIZE ((चिन्हित पूर्णांक)MW_DATA_WINDOW_SIZE)

bool esas2r_पढ़ो_flash_block(काष्ठा esas2r_adapter *a,
			     व्योम *to,
			     u32 from,
			     u32 size)
अणु
	u8 *end = (u8 *)to;

	/* Try to acquire access to the flash */
	अगर (!esas2r_flash_access(a, DRBL_FLASH_REQ))
		वापस false;

	जबतक (size) अणु
		u32 len;
		u32 offset;
		u32 iatvr;

		अगर (test_bit(AF2_SERIAL_FLASH, &a->flags2))
			iatvr = MW_DATA_ADDR_SER_FLASH + (from & -WINDOW_SIZE);
		अन्यथा
			iatvr = MW_DATA_ADDR_PAR_FLASH + (from & -WINDOW_SIZE);

		esas2r_map_data_winकरोw(a, iatvr);
		offset = from & (WINDOW_SIZE - 1);
		len = size;

		अगर (len > WINDOW_SIZE - offset)
			len = WINDOW_SIZE - offset;

		from += len;
		size -= len;

		जबतक (len--) अणु
			*end++ = esas2r_पढ़ो_data_byte(a, offset);
			offset++;
		पूर्ण
	पूर्ण

	/* Release flash access */
	esas2r_flash_access(a, DRBL_FLASH_DONE);
	वापस true;
पूर्ण

bool esas2r_पढ़ो_flash_rev(काष्ठा esas2r_adapter *a)
अणु
	u8 bytes[256];
	u16 *pw;
	u16 *pwstart;
	u16 type;
	u16 size;
	u32 sz;

	sz = माप(bytes);
	pw = (u16 *)(bytes + sz);
	pwstart = (u16 *)bytes + 2;

	अगर (!esas2r_पढ़ो_flash_block(a, bytes, FLS_OFFSET_CPYR - sz, sz))
		जाओ invalid_rev;

	जबतक (pw >= pwstart) अणु
		pw--;
		type = le16_to_cpu(*pw);
		pw--;
		size = le16_to_cpu(*pw);
		pw -= size / 2;

		अगर (type == FBT_CPYR
		    || type == FBT_SETUP
		    || pw < pwstart)
			जारी;

		अगर (type == FBT_FLASH_VER)
			a->flash_ver = le32_to_cpu(*(u32 *)pw);

		अवरोध;
	पूर्ण

invalid_rev:
	वापस esas2r_prपूर्णांक_flash_rev(a);
पूर्ण

bool esas2r_prपूर्णांक_flash_rev(काष्ठा esas2r_adapter *a)
अणु
	u16 year = LOWORD(a->flash_ver);
	u8 day = LOBYTE(HIWORD(a->flash_ver));
	u8 month = HIBYTE(HIWORD(a->flash_ver));

	अगर (day == 0
	    || month == 0
	    || day > 31
	    || month > 12
	    || year < 2006
	    || year > 9999) अणु
		म_नकल(a->flash_rev, "not found");
		a->flash_ver = 0;
		वापस false;
	पूर्ण

	प्र_लिखो(a->flash_rev, "%02d/%02d/%04d", month, day, year);
	esas2r_hdebug("flash version: %s", a->flash_rev);
	वापस true;
पूर्ण

/*
 * Find the type of boot image type that is currently in the flash.
 * The chip only has a 64 KB PCI-e expansion ROM
 * size so only one image can be flashed at a समय.
 */
bool esas2r_पढ़ो_image_type(काष्ठा esas2r_adapter *a)
अणु
	u8 bytes[256];
	काष्ठा esas2r_boot_image *bi;
	काष्ठा esas2r_boot_header *bh;
	u32 sz;
	u32 len;
	u32 offset;

	/* Start at the base of the boot images and look क्रम a valid image */
	sz = माप(bytes);
	len = FLS_LENGTH_BOOT;
	offset = 0;

	जबतक (true) अणु
		अगर (!esas2r_पढ़ो_flash_block(a, bytes, FLS_OFFSET_BOOT +
					     offset,
					     sz))
			जाओ invalid_rev;

		bi = (काष्ठा esas2r_boot_image *)bytes;
		bh = (काष्ठा esas2r_boot_header *)((u8 *)bi +
						   le16_to_cpu(
							   bi->header_offset));
		अगर (bi->signature != cpu_to_le16(0xAA55))
			जाओ invalid_rev;

		अगर (bh->code_type == CODE_TYPE_PC) अणु
			म_नकल(a->image_type, "BIOS");

			वापस true;
		पूर्ण अन्यथा अगर (bh->code_type == CODE_TYPE_EFI) अणु
			काष्ठा esas2r_efi_image *ei;

			/*
			 * So we have an EFI image.  There are several types
			 * so see which architecture we have.
			 */
			ei = (काष्ठा esas2r_efi_image *)bytes;

			चयन (le16_to_cpu(ei->machine_type)) अणु
			हाल EFI_MACHINE_IA32:
				म_नकल(a->image_type, "EFI 32-bit");
				वापस true;

			हाल EFI_MACHINE_IA64:
				म_नकल(a->image_type, "EFI itanium");
				वापस true;

			हाल EFI_MACHINE_X64:
				म_नकल(a->image_type, "EFI 64-bit");
				वापस true;

			हाल EFI_MACHINE_EBC:
				म_नकल(a->image_type, "EFI EBC");
				वापस true;

			शेष:
				जाओ invalid_rev;
			पूर्ण
		पूर्ण अन्यथा अणु
			u32 thislen;

			/* jump to the next image */
			thislen = (u32)le16_to_cpu(bh->image_length) * 512;
			अगर (thislen == 0
			    || thislen + offset > len
			    || bh->indicator == INDICATOR_LAST)
				अवरोध;

			offset += thislen;
		पूर्ण
	पूर्ण

invalid_rev:
	म_नकल(a->image_type, "no boot images");
	वापस false;
पूर्ण

/*
 *  Read and validate current NVRAM parameters by accessing
 *  physical NVRAM directly.  अगर currently stored parameters are
 *  invalid, use the शेषs.
 */
bool esas2r_nvram_पढ़ो_direct(काष्ठा esas2r_adapter *a)
अणु
	bool result;

	अगर (करोwn_पूर्णांकerruptible(&a->nvram_semaphore))
		वापस false;

	अगर (!esas2r_पढ़ो_flash_block(a, a->nvram, FLS_OFFSET_NVR,
				     माप(काष्ठा esas2r_sas_nvram))) अणु
		esas2r_hdebug("NVRAM read failed, using defaults");
		up(&a->nvram_semaphore);
		वापस false;
	पूर्ण

	result = esas2r_nvram_validate(a);

	up(&a->nvram_semaphore);

	वापस result;
पूर्ण

/* Interrupt callback to process NVRAM completions. */
अटल व्योम esas2r_nvram_callback(काष्ठा esas2r_adapter *a,
				  काष्ठा esas2r_request *rq)
अणु
	काष्ठा atto_vda_flash_req *vrq = &rq->vrq->flash;

	अगर (rq->req_stat == RS_SUCCESS) अणु
		/* last request was successful.  see what to करो now. */

		चयन (vrq->sub_func) अणु
		हाल VDA_FLASH_BEGINW:
			vrq->sub_func = VDA_FLASH_WRITE;
			rq->req_stat = RS_PENDING;
			अवरोध;

		हाल VDA_FLASH_WRITE:
			vrq->sub_func = VDA_FLASH_COMMIT;
			rq->req_stat = RS_PENDING;
			अवरोध;

		हाल VDA_FLASH_READ:
			esas2r_nvram_validate(a);
			अवरोध;

		हाल VDA_FLASH_COMMIT:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rq->req_stat != RS_PENDING) अणु
		/* update the NVRAM state */
		अगर (rq->req_stat == RS_SUCCESS)
			set_bit(AF_NVR_VALID, &a->flags);
		अन्यथा
			clear_bit(AF_NVR_VALID, &a->flags);

		esas2r_enable_heartbeat(a);

		up(&a->nvram_semaphore);
	पूर्ण
पूर्ण

/*
 * Write the contents of nvram to the adapter's physical NVRAM.
 * The cached copy of the NVRAM is also updated.
 */
bool esas2r_nvram_ग_लिखो(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq,
			काष्ठा esas2r_sas_nvram *nvram)
अणु
	काष्ठा esas2r_sas_nvram *n = nvram;
	u8 sas_address_bytes[8];
	u32 *sas_address_dwords = (u32 *)&sas_address_bytes[0];
	काष्ठा atto_vda_flash_req *vrq = &rq->vrq->flash;

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
		वापस false;

	अगर (करोwn_पूर्णांकerruptible(&a->nvram_semaphore))
		वापस false;

	अगर (n == शून्य)
		n = a->nvram;

	/* check the validity of the settings */
	अगर (n->version > SASNVR_VERSION) अणु
		up(&a->nvram_semaphore);
		वापस false;
	पूर्ण

	स_नकल(&sas_address_bytes[0], n->sas_addr, 8);

	अगर (sas_address_bytes[0] != 0x50
	    || sas_address_bytes[1] != 0x01
	    || sas_address_bytes[2] != 0x08
	    || (sas_address_bytes[3] & 0xF0) != 0x60
	    || ((sas_address_bytes[3] & 0x0F) | sas_address_dwords[1]) == 0) अणु
		up(&a->nvram_semaphore);
		वापस false;
	पूर्ण

	अगर (n->spin_up_delay > SASNVR_SPINUP_MAX)
		n->spin_up_delay = SASNVR_SPINUP_MAX;

	n->version = SASNVR_VERSION;
	n->checksum = n->checksum - esas2r_nvramcalc_cksum(n);
	स_नकल(a->nvram, n, माप(काष्ठा esas2r_sas_nvram));

	/* ग_लिखो the NVRAM */
	n = a->nvram;
	esas2r_disable_heartbeat(a);

	esas2r_build_flash_req(a,
			       rq,
			       VDA_FLASH_BEGINW,
			       esas2r_nvramcalc_xor_cksum(n),
			       FLS_OFFSET_NVR,
			       माप(काष्ठा esas2r_sas_nvram));

	अगर (test_bit(AF_LEGACY_SGE_MODE, &a->flags)) अणु

		vrq->data.sge[0].length =
			cpu_to_le32(SGE_LAST |
				    माप(काष्ठा esas2r_sas_nvram));
		vrq->data.sge[0].address = cpu_to_le64(
			a->uncached_phys + (u64)((u8 *)n - a->uncached));
	पूर्ण अन्यथा अणु
		vrq->data.prde[0].ctl_len =
			cpu_to_le32(माप(काष्ठा esas2r_sas_nvram));
		vrq->data.prde[0].address = cpu_to_le64(
			a->uncached_phys
			+ (u64)((u8 *)n - a->uncached));
	पूर्ण
	rq->पूर्णांकerrupt_cb = esas2r_nvram_callback;
	esas2r_start_request(a, rq);
	वापस true;
पूर्ण

/* Validate the cached NVRAM.  अगर the NVRAM is invalid, load the शेषs. */
bool esas2r_nvram_validate(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_sas_nvram *n = a->nvram;
	bool rslt = false;

	अगर (n->signature[0] != 'E'
	    || n->signature[1] != 'S'
	    || n->signature[2] != 'A'
	    || n->signature[3] != 'S') अणु
		esas2r_hdebug("invalid NVRAM signature");
	पूर्ण अन्यथा अगर (esas2r_nvramcalc_cksum(n)) अणु
		esas2r_hdebug("invalid NVRAM checksum");
	पूर्ण अन्यथा अगर (n->version > SASNVR_VERSION) अणु
		esas2r_hdebug("invalid NVRAM version");
	पूर्ण अन्यथा अणु
		set_bit(AF_NVR_VALID, &a->flags);
		rslt = true;
	पूर्ण

	अगर (rslt == false) अणु
		esas2r_hdebug("using defaults");
		esas2r_nvram_set_शेषs(a);
	पूर्ण

	वापस rslt;
पूर्ण

/*
 * Set the cached NVRAM to शेषs.  note that this function sets the शेष
 * NVRAM when it has been determined that the physical NVRAM is invalid.
 * In this हाल, the SAS address is fabricated.
 */
व्योम esas2r_nvram_set_शेषs(काष्ठा esas2r_adapter *a)
अणु
	काष्ठा esas2r_sas_nvram *n = a->nvram;
	u32 समय = jअगरfies_to_msecs(jअगरfies);

	clear_bit(AF_NVR_VALID, &a->flags);
	*n = शेष_sas_nvram;
	n->sas_addr[3] |= 0x0F;
	n->sas_addr[4] = HIBYTE(LOWORD(समय));
	n->sas_addr[5] = LOBYTE(LOWORD(समय));
	n->sas_addr[6] = a->pcid->bus->number;
	n->sas_addr[7] = a->pcid->devfn;
पूर्ण

व्योम esas2r_nvram_get_शेषs(काष्ठा esas2r_adapter *a,
			       काष्ठा esas2r_sas_nvram *nvram)
अणु
	u8 sas_addr[8];

	/*
	 * in हाल we are copying the शेषs पूर्णांकo the adapter, copy the SAS
	 * address out first.
	 */
	स_नकल(&sas_addr[0], a->nvram->sas_addr, 8);
	*nvram = शेष_sas_nvram;
	स_नकल(&nvram->sas_addr[0], &sas_addr[0], 8);
पूर्ण

bool esas2r_fm_api(काष्ठा esas2r_adapter *a, काष्ठा esas2r_flash_img *fi,
		   काष्ठा esas2r_request *rq, काष्ठा esas2r_sg_context *sgc)
अणु
	काष्ठा esas2r_flash_context *fc = &a->flash_context;
	u8 j;
	काष्ठा esas2r_component_header *ch;

	अगर (test_and_set_bit(AF_FLASH_LOCK, &a->flags)) अणु
		/* flag was alपढ़ोy set */
		fi->status = FI_STAT_BUSY;
		वापस false;
	पूर्ण

	स_नकल(&fc->sgc, sgc, माप(काष्ठा esas2r_sg_context));
	sgc = &fc->sgc;
	fc->fi = fi;
	fc->sgc_offset = sgc->cur_offset;
	rq->req_stat = RS_SUCCESS;
	rq->पूर्णांकerrupt_cx = fc;

	चयन (fi->fi_version) अणु
	हाल FI_VERSION_1:
		fc->scratch = ((काष्ठा esas2r_flash_img *)fi)->scratch_buf;
		fc->num_comps = FI_NUM_COMPS_V1;
		fc->fi_hdr_len = माप(काष्ठा esas2r_flash_img);
		अवरोध;

	शेष:
		वापस complete_fmapi_req(a, rq, FI_STAT_IMG_VER);
	पूर्ण

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
		वापस complete_fmapi_req(a, rq, FI_STAT_DEGRADED);

	चयन (fi->action) अणु
	हाल FI_ACT_DOWN: /* Download the components */
		/* Verअगरy the क्रमmat of the flash image */
		अगर (!verअगरy_fi(a, fc))
			वापस complete_fmapi_req(a, rq, fi->status);

		/* Adjust the BIOS fields that are dependent on the HBA */
		ch = &fi->cmp_hdr[CH_IT_BIOS];

		अगर (ch->length)
			fix_bios(a, fi);

		/* Adjust the EFI fields that are dependent on the HBA */
		ch = &fi->cmp_hdr[CH_IT_EFI];

		अगर (ch->length)
			fix_efi(a, fi);

		/*
		 * Since the image was just modअगरied, compute the checksum on
		 * the modअगरied image.  First update the CRC क्रम the composite
		 * expansion ROM image.
		 */
		fi->checksum = calc_fi_checksum(fc);

		/* Disable the heartbeat */
		esas2r_disable_heartbeat(a);

		/* Now start up the करोwnload sequence */
		fc->task = FMTSK_ERASE_BOOT;
		fc->func = VDA_FLASH_BEGINW;
		fc->comp_typ = CH_IT_CFG;
		fc->flsh_addr = FLS_OFFSET_BOOT;
		fc->sgc.length = FLS_LENGTH_BOOT;
		fc->sgc.cur_offset = शून्य;

		/* Setup the callback address */
		fc->पूर्णांकerrupt_cb = fw_करोwnload_proc;
		अवरोध;

	हाल FI_ACT_UPSZ: /* Get upload sizes */
		fi->adap_typ = get_fi_adap_type(a);
		fi->flags = 0;
		fi->num_comps = fc->num_comps;
		fi->length = fc->fi_hdr_len;

		/* Report the type of boot image in the rel_version string */
		स_नकल(fi->rel_version, a->image_type,
		       माप(fi->rel_version));

		/* Build the component headers */
		क्रम (j = 0, ch = fi->cmp_hdr;
		     j < fi->num_comps;
		     j++, ch++) अणु
			ch->img_type = j;
			ch->status = CH_STAT_PENDING;
			ch->length = 0;
			ch->version = 0xffffffff;
			ch->image_offset = 0;
			ch->pad[0] = 0;
			ch->pad[1] = 0;
		पूर्ण

		अगर (a->flash_ver != 0) अणु
			fi->cmp_hdr[CH_IT_BIOS].version =
				fi->cmp_hdr[CH_IT_MAC].version =
					fi->cmp_hdr[CH_IT_EFI].version =
						fi->cmp_hdr[CH_IT_CFG].version
							= a->flash_ver;

			fi->cmp_hdr[CH_IT_BIOS].status =
				fi->cmp_hdr[CH_IT_MAC].status =
					fi->cmp_hdr[CH_IT_EFI].status =
						fi->cmp_hdr[CH_IT_CFG].status =
							CH_STAT_SUCCESS;

			वापस complete_fmapi_req(a, rq, FI_STAT_SUCCESS);
		पूर्ण

		fallthrough;

	हाल FI_ACT_UP: /* Upload the components */
	शेष:
		वापस complete_fmapi_req(a, rq, FI_STAT_INVALID);
	पूर्ण

	/*
	 * If we make it here, fc has been setup to करो the first task.  Call
	 * load_image to क्रमmat the request, start it, and get out.  The
	 * पूर्णांकerrupt code will call the callback when the first message is
	 * complete.
	 */
	अगर (!load_image(a, rq))
		वापस complete_fmapi_req(a, rq, FI_STAT_FAILED);

	esas2r_start_request(a, rq);

	वापस true;
पूर्ण
