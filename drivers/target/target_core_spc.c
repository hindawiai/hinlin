<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SCSI Primary Commands (SPC) parsing and emulation.
 *
 * (c) Copyright 2002-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/scsi_common.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_alua.h"
#समावेश "target_core_pr.h"
#समावेश "target_core_ua.h"
#समावेश "target_core_xcopy.h"

अटल व्योम spc_fill_alua_data(काष्ठा se_lun *lun, अचिन्हित अक्षर *buf)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;

	/*
	 * Set SCCS क्रम MAINTEन_अंकCE_IN + REPORT_TARGET_PORT_GROUPS.
	 */
	buf[5]	= 0x80;

	/*
	 * Set TPGS field क्रम explicit and/or implicit ALUA access type
	 * and opteration.
	 *
	 * See spc4r17 section 6.4.2 Table 135
	 */
	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	अगर (tg_pt_gp)
		buf[5] |= tg_pt_gp->tg_pt_gp_alua_access_type;
	spin_unlock(&lun->lun_tg_pt_gp_lock);
पूर्ण

sense_reason_t
spc_emulate_inquiry_std(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	काष्ठा se_lun *lun = cmd->se_lun;
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *sess = cmd->se_sess;

	/* Set RMB (removable media) क्रम tape devices */
	अगर (dev->transport->get_device_type(dev) == TYPE_TAPE)
		buf[1] = 0x80;

	buf[2] = 0x05; /* SPC-3 */

	/*
	 * NORMACA and HISUP = 0, RESPONSE DATA FORMAT = 2
	 *
	 * SPC4 says:
	 *   A RESPONSE DATA FORMAT field set to 2h indicates that the
	 *   standard INQUIRY data is in the क्रमmat defined in this
	 *   standard. Response data क्रमmat values less than 2h are
	 *   obsolete. Response data क्रमmat values greater than 2h are
	 *   reserved.
	 */
	buf[3] = 2;

	/*
	 * Enable SCCS and TPGS fields क्रम Emulated ALUA
	 */
	spc_fill_alua_data(lun, buf);

	/*
	 * Set Third-Party Copy (3PC) bit to indicate support क्रम EXTENDED_COPY
	 */
	अगर (dev->dev_attrib.emulate_3pc)
		buf[5] |= 0x8;
	/*
	 * Set Protection (PROTECT) bit when DIF has been enabled on the
	 * device, and the fabric supports VERIFY + PASS.  Also report
	 * PROTECT=1 अगर sess_prot_type has been configured to allow T10-PI
	 * to unरक्षित devices.
	 */
	अगर (sess->sup_prot_ops & (TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS)) अणु
		अगर (dev->dev_attrib.pi_prot_type || cmd->se_sess->sess_prot_type)
			buf[5] |= 0x1;
	पूर्ण

	buf[7] = 0x2; /* CmdQue=1 */

	/*
	 * ASCII data fields described as being left-aligned shall have any
	 * unused bytes at the end of the field (i.e., highest offset) and the
	 * unused bytes shall be filled with ASCII space अक्षरacters (20h).
	 */
	स_रखो(&buf[8], 0x20,
	       INQUIRY_VENDOR_LEN + INQUIRY_MODEL_LEN + INQUIRY_REVISION_LEN);
	स_नकल(&buf[8], dev->t10_wwn.venकरोr,
	       strnlen(dev->t10_wwn.venकरोr, INQUIRY_VENDOR_LEN));
	स_नकल(&buf[16], dev->t10_wwn.model,
	       strnlen(dev->t10_wwn.model, INQUIRY_MODEL_LEN));
	स_नकल(&buf[32], dev->t10_wwn.revision,
	       strnlen(dev->t10_wwn.revision, INQUIRY_REVISION_LEN));
	buf[4] = 31; /* Set additional length to 31 */

	वापस 0;
पूर्ण
EXPORT_SYMBOL(spc_emulate_inquiry_std);

/* unit serial number */
अटल sense_reason_t
spc_emulate_evpd_80(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	u16 len;

	अगर (dev->dev_flags & DF_EMULATED_VPD_UNIT_SERIAL) अणु
		len = प्र_लिखो(&buf[4], "%s", dev->t10_wwn.unit_serial);
		len++; /* Extra Byte क्रम शून्य Terminator */
		buf[3] = len;
	पूर्ण
	वापस 0;
पूर्ण

व्योम spc_parse_naa_6h_venकरोr_specअगरic(काष्ठा se_device *dev,
				      अचिन्हित अक्षर *buf)
अणु
	अचिन्हित अक्षर *p = &dev->t10_wwn.unit_serial[0];
	पूर्णांक cnt;
	bool next = true;

	/*
	 * Generate up to 36 bits of VENDOR SPECIFIC IDENTIFIER starting on
	 * byte 3 bit 3-0 क्रम NAA IEEE Registered Extended DESIGNATOR field
	 * क्रमmat, followed by 64 bits of VENDOR SPECIFIC IDENTIFIER EXTENSION
	 * to complete the payload.  These are based from VPD=0x80 PRODUCT SERIAL
	 * NUMBER set via vpd_unit_serial in target_core_configfs.c to ensure
	 * per device uniqeness.
	 */
	क्रम (cnt = 0; *p && cnt < 13; p++) अणु
		पूर्णांक val = hex_to_bin(*p);

		अगर (val < 0)
			जारी;

		अगर (next) अणु
			next = false;
			buf[cnt++] |= val;
		पूर्ण अन्यथा अणु
			next = true;
			buf[cnt] = val << 4;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Device identअगरication VPD, क्रम a complete list of
 * DESIGNATOR TYPEs see spc4r17 Table 459.
 */
sense_reason_t
spc_emulate_evpd_83(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_lun *lun = cmd->se_lun;
	काष्ठा se_portal_group *tpg = शून्य;
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem;
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	अचिन्हित अक्षर *prod = &dev->t10_wwn.model[0];
	u32 prod_len;
	u32 unit_serial_len, off = 0;
	u16 len = 0, id_len;

	off = 4;

	/*
	 * NAA IEEE Registered Extended Asचिन्हित designator क्रमmat, see
	 * spc4r17 section 7.7.3.6.5
	 *
	 * We depend upon a target_core_mod/ConfigFS provided
	 * /sys/kernel/config/target/core/$HBA/$DEV/wwn/vpd_unit_serial
	 * value in order to वापस the NAA id.
	 */
	अगर (!(dev->dev_flags & DF_EMULATED_VPD_UNIT_SERIAL))
		जाओ check_t10_vend_desc;

	/* CODE SET == Binary */
	buf[off++] = 0x1;

	/* Set ASSOCIATION == addressed logical unit: 0)b */
	buf[off] = 0x00;

	/* Identअगरier/Designator type == NAA identअगरier */
	buf[off++] |= 0x3;
	off++;

	/* Identअगरier/Designator length */
	buf[off++] = 0x10;

	/*
	 * Start NAA IEEE Registered Extended Identअगरier/Designator
	 */
	buf[off++] = (0x6 << 4);

	/*
	 * Use OpenFabrics IEEE Company ID: 00 14 05
	 */
	buf[off++] = 0x01;
	buf[off++] = 0x40;
	buf[off] = (0x5 << 4);

	/*
	 * Return ConfigFS Unit Serial Number inक्रमmation क्रम
	 * VENDOR_SPECIFIC_IDENTIFIER and
	 * VENDOR_SPECIFIC_IDENTIFIER_EXTENTION
	 */
	spc_parse_naa_6h_venकरोr_specअगरic(dev, &buf[off]);

	len = 20;
	off = (len + 4);

check_t10_vend_desc:
	/*
	 * T10 Venकरोr Identअगरier Page, see spc4r17 section 7.7.3.4
	 */
	id_len = 8; /* For Venकरोr field */
	prod_len = 4; /* For VPD Header */
	prod_len += 8; /* For Venकरोr field */
	prod_len += म_माप(prod);
	prod_len++; /* For : */

	अगर (dev->dev_flags & DF_EMULATED_VPD_UNIT_SERIAL) अणु
		unit_serial_len = म_माप(&dev->t10_wwn.unit_serial[0]);
		unit_serial_len++; /* For शून्य Terminator */

		id_len += प्र_लिखो(&buf[off+12], "%s:%s", prod,
				&dev->t10_wwn.unit_serial[0]);
	पूर्ण
	buf[off] = 0x2; /* ASCII */
	buf[off+1] = 0x1; /* T10 Venकरोr ID */
	buf[off+2] = 0x0;
	/* left align Venकरोr ID and pad with spaces */
	स_रखो(&buf[off+4], 0x20, INQUIRY_VENDOR_LEN);
	स_नकल(&buf[off+4], dev->t10_wwn.venकरोr,
	       strnlen(dev->t10_wwn.venकरोr, INQUIRY_VENDOR_LEN));
	/* Extra Byte क्रम शून्य Terminator */
	id_len++;
	/* Identअगरier Length */
	buf[off+3] = id_len;
	/* Header size क्रम Designation descriptor */
	len += (id_len + 4);
	off += (id_len + 4);

	अगर (1) अणु
		काष्ठा t10_alua_lu_gp *lu_gp;
		u32 padding, scsi_name_len, scsi_target_len;
		u16 lu_gp_id = 0;
		u16 tg_pt_gp_id = 0;
		u16 tpgt;

		tpg = lun->lun_tpg;
		/*
		 * Relative target port identअगरer, see spc4r17
		 * section 7.7.3.7
		 *
		 * Get the PROTOCOL IDENTIFIER as defined by spc4r17
		 * section 7.5.1 Table 362
		 */
		buf[off] = tpg->proto_id << 4;
		buf[off++] |= 0x1; /* CODE SET == Binary */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == target port: 01b */
		buf[off] |= 0x10;
		/* DESIGNATOR TYPE == Relative target port identअगरer */
		buf[off++] |= 0x4;
		off++; /* Skip over Reserved */
		buf[off++] = 4; /* DESIGNATOR LENGTH */
		/* Skip over Obsolete field in RTPI payload
		 * in Table 472 */
		off += 2;
		put_unaligned_be16(lun->lun_rtpi, &buf[off]);
		off += 2;
		len += 8; /* Header size + Designation descriptor */
		/*
		 * Target port group identअगरier, see spc4r17
		 * section 7.7.3.8
		 *
		 * Get the PROTOCOL IDENTIFIER as defined by spc4r17
		 * section 7.5.1 Table 362
		 */
		spin_lock(&lun->lun_tg_pt_gp_lock);
		tg_pt_gp = lun->lun_tg_pt_gp;
		अगर (!tg_pt_gp) अणु
			spin_unlock(&lun->lun_tg_pt_gp_lock);
			जाओ check_lu_gp;
		पूर्ण
		tg_pt_gp_id = tg_pt_gp->tg_pt_gp_id;
		spin_unlock(&lun->lun_tg_pt_gp_lock);

		buf[off] = tpg->proto_id << 4;
		buf[off++] |= 0x1; /* CODE SET == Binary */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == target port: 01b */
		buf[off] |= 0x10;
		/* DESIGNATOR TYPE == Target port group identअगरier */
		buf[off++] |= 0x5;
		off++; /* Skip over Reserved */
		buf[off++] = 4; /* DESIGNATOR LENGTH */
		off += 2; /* Skip over Reserved Field */
		put_unaligned_be16(tg_pt_gp_id, &buf[off]);
		off += 2;
		len += 8; /* Header size + Designation descriptor */
		/*
		 * Logical Unit Group identअगरier, see spc4r17
		 * section 7.7.3.8
		 */
check_lu_gp:
		lu_gp_mem = dev->dev_alua_lu_gp_mem;
		अगर (!lu_gp_mem)
			जाओ check_scsi_name;

		spin_lock(&lu_gp_mem->lu_gp_mem_lock);
		lu_gp = lu_gp_mem->lu_gp;
		अगर (!lu_gp) अणु
			spin_unlock(&lu_gp_mem->lu_gp_mem_lock);
			जाओ check_scsi_name;
		पूर्ण
		lu_gp_id = lu_gp->lu_gp_id;
		spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

		buf[off++] |= 0x1; /* CODE SET == Binary */
		/* DESIGNATOR TYPE == Logical Unit Group identअगरier */
		buf[off++] |= 0x6;
		off++; /* Skip over Reserved */
		buf[off++] = 4; /* DESIGNATOR LENGTH */
		off += 2; /* Skip over Reserved Field */
		put_unaligned_be16(lu_gp_id, &buf[off]);
		off += 2;
		len += 8; /* Header size + Designation descriptor */
		/*
		 * SCSI name string designator, see spc4r17
		 * section 7.7.3.11
		 *
		 * Get the PROTOCOL IDENTIFIER as defined by spc4r17
		 * section 7.5.1 Table 362
		 */
check_scsi_name:
		buf[off] = tpg->proto_id << 4;
		buf[off++] |= 0x3; /* CODE SET == UTF-8 */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == target port: 01b */
		buf[off] |= 0x10;
		/* DESIGNATOR TYPE == SCSI name string */
		buf[off++] |= 0x8;
		off += 2; /* Skip over Reserved and length */
		/*
		 * SCSI name string identअगरer containing, $FABRIC_MOD
		 * dependent inक्रमmation.  For LIO-Target and iSCSI
		 * Target Port, this means "<iSCSI name>,t,0x<TPGT> in
		 * UTF-8 encoding.
		 */
		tpgt = tpg->se_tpg_tfo->tpg_get_tag(tpg);
		scsi_name_len = प्र_लिखो(&buf[off], "%s,t,0x%04x",
					tpg->se_tpg_tfo->tpg_get_wwn(tpg), tpgt);
		scsi_name_len += 1 /* Include  शून्य terminator */;
		/*
		 * The null-terminated, null-padded (see 4.4.2) SCSI
		 * NAME STRING field contains a UTF-8 क्रमmat string.
		 * The number of bytes in the SCSI NAME STRING field
		 * (i.e., the value in the DESIGNATOR LENGTH field)
		 * shall be no larger than 256 and shall be a multiple
		 * of four.
		 */
		padding = ((-scsi_name_len) & 3);
		अगर (padding)
			scsi_name_len += padding;
		अगर (scsi_name_len > 256)
			scsi_name_len = 256;

		buf[off-1] = scsi_name_len;
		off += scsi_name_len;
		/* Header size + Designation descriptor */
		len += (scsi_name_len + 4);

		/*
		 * Target device designator
		 */
		buf[off] = tpg->proto_id << 4;
		buf[off++] |= 0x3; /* CODE SET == UTF-8 */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == target device: 10b */
		buf[off] |= 0x20;
		/* DESIGNATOR TYPE == SCSI name string */
		buf[off++] |= 0x8;
		off += 2; /* Skip over Reserved and length */
		/*
		 * SCSI name string identअगरer containing, $FABRIC_MOD
		 * dependent inक्रमmation.  For LIO-Target and iSCSI
		 * Target Port, this means "<iSCSI name>" in
		 * UTF-8 encoding.
		 */
		scsi_target_len = प्र_लिखो(&buf[off], "%s",
					  tpg->se_tpg_tfo->tpg_get_wwn(tpg));
		scsi_target_len += 1 /* Include  शून्य terminator */;
		/*
		 * The null-terminated, null-padded (see 4.4.2) SCSI
		 * NAME STRING field contains a UTF-8 क्रमmat string.
		 * The number of bytes in the SCSI NAME STRING field
		 * (i.e., the value in the DESIGNATOR LENGTH field)
		 * shall be no larger than 256 and shall be a multiple
		 * of four.
		 */
		padding = ((-scsi_target_len) & 3);
		अगर (padding)
			scsi_target_len += padding;
		अगर (scsi_target_len > 256)
			scsi_target_len = 256;

		buf[off-1] = scsi_target_len;
		off += scsi_target_len;

		/* Header size + Designation descriptor */
		len += (scsi_target_len + 4);
	पूर्ण
	put_unaligned_be16(len, &buf[2]); /* Page Length क्रम VPD 0x83 */
	वापस 0;
पूर्ण
EXPORT_SYMBOL(spc_emulate_evpd_83);

/* Extended INQUIRY Data VPD Page */
अटल sense_reason_t
spc_emulate_evpd_86(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *sess = cmd->se_sess;

	buf[3] = 0x3c;
	/*
	 * Set GRD_CHK + REF_CHK क्रम TYPE1 protection, or GRD_CHK
	 * only क्रम TYPE3 protection.
	 */
	अगर (sess->sup_prot_ops & (TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS)) अणु
		अगर (dev->dev_attrib.pi_prot_type == TARGET_DIF_TYPE1_PROT ||
		    cmd->se_sess->sess_prot_type == TARGET_DIF_TYPE1_PROT)
			buf[4] = 0x5;
		अन्यथा अगर (dev->dev_attrib.pi_prot_type == TARGET_DIF_TYPE3_PROT ||
			 cmd->se_sess->sess_prot_type == TARGET_DIF_TYPE3_PROT)
			buf[4] = 0x4;
	पूर्ण

	/* logical unit supports type 1 and type 3 protection */
	अगर ((dev->transport->get_device_type(dev) == TYPE_DISK) &&
	    (sess->sup_prot_ops & (TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS)) &&
	    (dev->dev_attrib.pi_prot_type || cmd->se_sess->sess_prot_type)) अणु
		buf[4] |= (0x3 << 3);
	पूर्ण

	/* Set HEADSUP, ORDSUP, SIMPSUP */
	buf[5] = 0x07;

	/* If WriteCache emulation is enabled, set V_SUP */
	अगर (target_check_wce(dev))
		buf[6] = 0x01;
	/* If an LBA map is present set R_SUP */
	spin_lock(&cmd->se_dev->t10_alua.lba_map_lock);
	अगर (!list_empty(&dev->t10_alua.lba_map_list))
		buf[8] = 0x10;
	spin_unlock(&cmd->se_dev->t10_alua.lba_map_lock);
	वापस 0;
पूर्ण

/* Block Limits VPD page */
अटल sense_reason_t
spc_emulate_evpd_b0(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	u32 mtl = 0;
	पूर्णांक have_tp = 0, opt, min;

	/*
	 * Following spc3r22 section 6.5.3 Block Limits VPD page, when
	 * emulate_tpu=1 or emulate_tpws=1 we will be expect a
	 * dअगरferent page length क्रम Thin Provisioning.
	 */
	अगर (dev->dev_attrib.emulate_tpu || dev->dev_attrib.emulate_tpws)
		have_tp = 1;

	buf[0] = dev->transport->get_device_type(dev);
	buf[3] = have_tp ? 0x3c : 0x10;

	/* Set WSNZ to 1 */
	buf[4] = 0x01;
	/*
	 * Set MAXIMUM COMPARE AND WRITE LENGTH
	 */
	अगर (dev->dev_attrib.emulate_caw)
		buf[5] = 0x01;

	/*
	 * Set OPTIMAL TRANSFER LENGTH GRANULARITY
	 */
	अगर (dev->transport->get_io_min && (min = dev->transport->get_io_min(dev)))
		put_unaligned_be16(min / dev->dev_attrib.block_size, &buf[6]);
	अन्यथा
		put_unaligned_be16(1, &buf[6]);

	/*
	 * Set MAXIMUM TRANSFER LENGTH
	 *
	 * XXX: Currently assumes single PAGE_SIZE per scatterlist क्रम fabrics
	 * enक्रमcing maximum HW scatter-gather-list entry limit
	 */
	अगर (cmd->se_tfo->max_data_sg_nents) अणु
		mtl = (cmd->se_tfo->max_data_sg_nents * PAGE_SIZE) /
		       dev->dev_attrib.block_size;
	पूर्ण
	put_unaligned_be32(min_not_zero(mtl, dev->dev_attrib.hw_max_sectors), &buf[8]);

	/*
	 * Set OPTIMAL TRANSFER LENGTH
	 */
	अगर (dev->transport->get_io_opt && (opt = dev->transport->get_io_opt(dev)))
		put_unaligned_be32(opt / dev->dev_attrib.block_size, &buf[12]);
	अन्यथा
		put_unaligned_be32(dev->dev_attrib.optimal_sectors, &buf[12]);

	/*
	 * Exit now अगर we करोn't support TP.
	 */
	अगर (!have_tp)
		जाओ max_ग_लिखो_same;

	/*
	 * Set MAXIMUM UNMAP LBA COUNT
	 */
	put_unaligned_be32(dev->dev_attrib.max_unmap_lba_count, &buf[20]);

	/*
	 * Set MAXIMUM UNMAP BLOCK DESCRIPTOR COUNT
	 */
	put_unaligned_be32(dev->dev_attrib.max_unmap_block_desc_count,
			   &buf[24]);

	/*
	 * Set OPTIMAL UNMAP GRANULARITY
	 */
	put_unaligned_be32(dev->dev_attrib.unmap_granularity, &buf[28]);

	/*
	 * UNMAP GRANULARITY ALIGNMENT
	 */
	put_unaligned_be32(dev->dev_attrib.unmap_granularity_alignment,
			   &buf[32]);
	अगर (dev->dev_attrib.unmap_granularity_alignment != 0)
		buf[32] |= 0x80; /* Set the UGAVALID bit */

	/*
	 * MAXIMUM WRITE SAME LENGTH
	 */
max_ग_लिखो_same:
	put_unaligned_be64(dev->dev_attrib.max_ग_लिखो_same_len, &buf[36]);

	वापस 0;
पूर्ण

/* Block Device Characteristics VPD page */
अटल sense_reason_t
spc_emulate_evpd_b1(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	काष्ठा se_device *dev = cmd->se_dev;

	buf[0] = dev->transport->get_device_type(dev);
	buf[3] = 0x3c;
	buf[5] = dev->dev_attrib.is_nonrot ? 1 : 0;

	वापस 0;
पूर्ण

/* Thin Provisioning VPD */
अटल sense_reason_t
spc_emulate_evpd_b2(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	काष्ठा se_device *dev = cmd->se_dev;

	/*
	 * From spc3r22 section 6.5.4 Thin Provisioning VPD page:
	 *
	 * The PAGE LENGTH field is defined in SPC-4. If the DP bit is set to
	 * zero, then the page length shall be set to 0004h.  If the DP bit
	 * is set to one, then the page length shall be set to the value
	 * defined in table 162.
	 */
	buf[0] = dev->transport->get_device_type(dev);

	/*
	 * Set Hardcoded length mentioned above क्रम DP=0
	 */
	put_unaligned_be16(0x0004, &buf[2]);

	/*
	 * The THRESHOLD EXPONENT field indicates the threshold set size in
	 * LBAs as a घातer of 2 (i.e., the threshold set size is equal to
	 * 2(threshold exponent)).
	 *
	 * Note that this is currently set to 0x00 as mkp says it will be
	 * changing again.  We can enable this once it has settled in T10
	 * and is actually used by Linux/SCSI ML code.
	 */
	buf[4] = 0x00;

	/*
	 * A TPU bit set to one indicates that the device server supports
	 * the UNMAP command (see 5.25). A TPU bit set to zero indicates
	 * that the device server करोes not support the UNMAP command.
	 */
	अगर (dev->dev_attrib.emulate_tpu != 0)
		buf[5] = 0x80;

	/*
	 * A TPWS bit set to one indicates that the device server supports
	 * the use of the WRITE SAME (16) command (see 5.42) to unmap LBAs.
	 * A TPWS bit set to zero indicates that the device server करोes not
	 * support the use of the WRITE SAME (16) command to unmap LBAs.
	 */
	अगर (dev->dev_attrib.emulate_tpws != 0)
		buf[5] |= 0x40 | 0x20;

	/*
	 * The unmap_zeroes_data set means that the underlying device supports
	 * REQ_OP_DISCARD and has the discard_zeroes_data bit set. This
	 * satisfies the SBC requirements क्रम LBPRZ, meaning that a subsequent
	 * पढ़ो will वापस zeroes after an UNMAP or WRITE SAME (16) to an LBA
	 * See sbc4r36 6.6.4.
	 */
	अगर (((dev->dev_attrib.emulate_tpu != 0) ||
	     (dev->dev_attrib.emulate_tpws != 0)) &&
	     (dev->dev_attrib.unmap_zeroes_data != 0))
		buf[5] |= 0x04;

	वापस 0;
पूर्ण

/* Referrals VPD page */
अटल sense_reason_t
spc_emulate_evpd_b3(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	काष्ठा se_device *dev = cmd->se_dev;

	buf[0] = dev->transport->get_device_type(dev);
	buf[3] = 0x0c;
	put_unaligned_be32(dev->t10_alua.lba_map_segment_size, &buf[8]);
	put_unaligned_be32(dev->t10_alua.lba_map_segment_multiplier, &buf[12]);

	वापस 0;
पूर्ण

अटल sense_reason_t
spc_emulate_evpd_00(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf);

अटल काष्ठा अणु
	uपूर्णांक8_t		page;
	sense_reason_t	(*emulate)(काष्ठा se_cmd *, अचिन्हित अक्षर *);
पूर्ण evpd_handlers[] = अणु
	अणु .page = 0x00, .emulate = spc_emulate_evpd_00 पूर्ण,
	अणु .page = 0x80, .emulate = spc_emulate_evpd_80 पूर्ण,
	अणु .page = 0x83, .emulate = spc_emulate_evpd_83 पूर्ण,
	अणु .page = 0x86, .emulate = spc_emulate_evpd_86 पूर्ण,
	अणु .page = 0xb0, .emulate = spc_emulate_evpd_b0 पूर्ण,
	अणु .page = 0xb1, .emulate = spc_emulate_evpd_b1 पूर्ण,
	अणु .page = 0xb2, .emulate = spc_emulate_evpd_b2 पूर्ण,
	अणु .page = 0xb3, .emulate = spc_emulate_evpd_b3 पूर्ण,
पूर्ण;

/* supported vital product data pages */
अटल sense_reason_t
spc_emulate_evpd_00(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक p;

	/*
	 * Only report the INQUIRY EVPD=1 pages after a valid NAA
	 * Registered Extended LUN WWN has been set via ConfigFS
	 * during device creation/restart.
	 */
	अगर (cmd->se_dev->dev_flags & DF_EMULATED_VPD_UNIT_SERIAL) अणु
		buf[3] = ARRAY_SIZE(evpd_handlers);
		क्रम (p = 0; p < ARRAY_SIZE(evpd_handlers); ++p)
			buf[p + 4] = evpd_handlers[p].page;
	पूर्ण

	वापस 0;
पूर्ण

अटल sense_reason_t
spc_emulate_inquiry(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित अक्षर *rbuf;
	अचिन्हित अक्षर *cdb = cmd->t_task_cdb;
	अचिन्हित अक्षर *buf;
	sense_reason_t ret;
	पूर्णांक p;
	पूर्णांक len = 0;

	buf = kzalloc(SE_INQUIRY_BUF, GFP_KERNEL);
	अगर (!buf) अणु
		pr_err("Unable to allocate response buffer for INQUIRY\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण

	buf[0] = dev->transport->get_device_type(dev);

	अगर (!(cdb[1] & 0x1)) अणु
		अगर (cdb[2]) अणु
			pr_err("INQUIRY with EVPD==0 but PAGE CODE=%02x\n",
			       cdb[2]);
			ret = TCM_INVALID_CDB_FIELD;
			जाओ out;
		पूर्ण

		ret = spc_emulate_inquiry_std(cmd, buf);
		len = buf[4] + 5;
		जाओ out;
	पूर्ण

	क्रम (p = 0; p < ARRAY_SIZE(evpd_handlers); ++p) अणु
		अगर (cdb[2] == evpd_handlers[p].page) अणु
			buf[1] = cdb[2];
			ret = evpd_handlers[p].emulate(cmd, buf);
			len = get_unaligned_be16(&buf[2]) + 4;
			जाओ out;
		पूर्ण
	पूर्ण

	pr_err("Unknown VPD Code: 0x%02x\n", cdb[2]);
	ret = TCM_INVALID_CDB_FIELD;

out:
	rbuf = transport_kmap_data_sg(cmd);
	अगर (rbuf) अणु
		स_नकल(rbuf, buf, min_t(u32, SE_INQUIRY_BUF, cmd->data_length));
		transport_kunmap_data_sg(cmd);
	पूर्ण
	kमुक्त(buf);

	अगर (!ret)
		target_complete_cmd_with_length(cmd, GOOD, len);
	वापस ret;
पूर्ण

अटल पूर्णांक spc_modesense_rwrecovery(काष्ठा se_cmd *cmd, u8 pc, u8 *p)
अणु
	p[0] = 0x01;
	p[1] = 0x0a;

	/* No changeable values क्रम now */
	अगर (pc == 1)
		जाओ out;

out:
	वापस 12;
पूर्ण

अटल पूर्णांक spc_modesense_control(काष्ठा se_cmd *cmd, u8 pc, u8 *p)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *sess = cmd->se_sess;

	p[0] = 0x0a;
	p[1] = 0x0a;

	/* No changeable values क्रम now */
	अगर (pc == 1)
		जाओ out;

	/* GLTSD: No implicit save of log parameters */
	p[2] = (1 << 1);
	अगर (target_sense_desc_क्रमmat(dev))
		/* D_SENSE: Descriptor क्रमmat sense data क्रम 64bit sectors */
		p[2] |= (1 << 2);

	/*
	 * From spc4r23, 7.4.7 Control mode page
	 *
	 * The QUEUE ALGORITHM MODIFIER field (see table 368) specअगरies
	 * restrictions on the algorithm used क्रम reordering commands
	 * having the SIMPLE task attribute (see SAM-4).
	 *
	 *                    Table 368 -- QUEUE ALGORITHM MODIFIER field
	 *                         Code      Description
	 *                          0h       Restricted reordering
	 *                          1h       Unrestricted reordering allowed
	 *                          2h to 7h    Reserved
	 *                          8h to Fh    Venकरोr specअगरic
	 *
	 * A value of zero in the QUEUE ALGORITHM MODIFIER field specअगरies that
	 * the device server shall order the processing sequence of commands
	 * having the SIMPLE task attribute such that data पूर्णांकegrity is मुख्यtained
	 * क्रम that I_T nexus (i.e., अगर the transmission of new SCSI transport protocol
	 * requests is halted at any समय, the final value of all data observable
	 * on the medium shall be the same as अगर all the commands had been processed
	 * with the ORDERED task attribute).
	 *
	 * A value of one in the QUEUE ALGORITHM MODIFIER field specअगरies that the
	 * device server may reorder the processing sequence of commands having the
	 * SIMPLE task attribute in any manner. Any data पूर्णांकegrity exposures related to
	 * command sequence order shall be explicitly handled by the application client
	 * through the selection of appropriate ommands and task attributes.
	 */
	p[3] = (dev->dev_attrib.emulate_rest_reord == 1) ? 0x00 : 0x10;
	/*
	 * From spc4r17, section 7.4.6 Control mode Page
	 *
	 * Unit Attention पूर्णांकerlocks control (UN_INTLCK_CTRL) to code 00b
	 *
	 * 00b: The logical unit shall clear any unit attention condition
	 * reported in the same I_T_L_Q nexus transaction as a CHECK CONDITION
	 * status and shall not establish a unit attention condition when a com-
	 * mand is completed with BUSY, TASK SET FULL, or RESERVATION CONFLICT
	 * status.
	 *
	 * 10b: The logical unit shall not clear any unit attention condition
	 * reported in the same I_T_L_Q nexus transaction as a CHECK CONDITION
	 * status and shall not establish a unit attention condition when
	 * a command is completed with BUSY, TASK SET FULL, or RESERVATION
	 * CONFLICT status.
	 *
	 * 11b a The logical unit shall not clear any unit attention condition
	 * reported in the same I_T_L_Q nexus transaction as a CHECK CONDITION
	 * status and shall establish a unit attention condition क्रम the
	 * initiator port associated with the I_T nexus on which the BUSY,
	 * TASK SET FULL, or RESERVATION CONFLICT status is being वापसed.
	 * Depending on the status, the additional sense code shall be set to
	 * PREVIOUS BUSY STATUS, PREVIOUS TASK SET FULL STATUS, or PREVIOUS
	 * RESERVATION CONFLICT STATUS. Until it is cleared by a REQUEST SENSE
	 * command, a unit attention condition shall be established only once
	 * क्रम a BUSY, TASK SET FULL, or RESERVATION CONFLICT status regardless
	 * to the number of commands completed with one of those status codes.
	 */
	चयन (dev->dev_attrib.emulate_ua_पूर्णांकlck_ctrl) अणु
	हाल TARGET_UA_INTLCK_CTRL_ESTABLISH_UA:
		p[4] = 0x30;
		अवरोध;
	हाल TARGET_UA_INTLCK_CTRL_NO_CLEAR:
		p[4] = 0x20;
		अवरोध;
	शेष:	/* TARGET_UA_INTLCK_CTRL_CLEAR */
		p[4] = 0x00;
		अवरोध;
	पूर्ण
	/*
	 * From spc4r17, section 7.4.6 Control mode Page
	 *
	 * Task Aborted Status (TAS) bit set to zero.
	 *
	 * A task पातed status (TAS) bit set to zero specअगरies that पातed
	 * tasks shall be terminated by the device server without any response
	 * to the application client. A TAS bit set to one specअगरies that tasks
	 * पातed by the actions of an I_T nexus other than the I_T nexus on
	 * which the command was received shall be completed with TASK ABORTED
	 * status (see SAM-4).
	 */
	p[5] = (dev->dev_attrib.emulate_tas) ? 0x40 : 0x00;
	/*
	 * From spc4r30, section 7.5.7 Control mode page
	 *
	 * Application Tag Owner (ATO) bit set to one.
	 *
	 * If the ATO bit is set to one the device server shall not modअगरy the
	 * LOGICAL BLOCK APPLICATION TAG field and, depending on the protection
	 * type, shall not modअगरy the contents of the LOGICAL BLOCK REFERENCE
	 * TAG field.
	 */
	अगर (sess->sup_prot_ops & (TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS)) अणु
		अगर (dev->dev_attrib.pi_prot_type || sess->sess_prot_type)
			p[5] |= 0x80;
	पूर्ण

	p[8] = 0xff;
	p[9] = 0xff;
	p[11] = 30;

out:
	वापस 12;
पूर्ण

अटल पूर्णांक spc_modesense_caching(काष्ठा se_cmd *cmd, u8 pc, u8 *p)
अणु
	काष्ठा se_device *dev = cmd->se_dev;

	p[0] = 0x08;
	p[1] = 0x12;

	/* No changeable values क्रम now */
	अगर (pc == 1)
		जाओ out;

	अगर (target_check_wce(dev))
		p[2] = 0x04; /* Write Cache Enable */
	p[12] = 0x20; /* Disabled Read Ahead */

out:
	वापस 20;
पूर्ण

अटल पूर्णांक spc_modesense_inक्रमmational_exceptions(काष्ठा se_cmd *cmd, u8 pc, अचिन्हित अक्षर *p)
अणु
	p[0] = 0x1c;
	p[1] = 0x0a;

	/* No changeable values क्रम now */
	अगर (pc == 1)
		जाओ out;

out:
	वापस 12;
पूर्ण

अटल काष्ठा अणु
	uपूर्णांक8_t		page;
	uपूर्णांक8_t		subpage;
	पूर्णांक		(*emulate)(काष्ठा se_cmd *, u8, अचिन्हित अक्षर *);
पूर्ण modesense_handlers[] = अणु
	अणु .page = 0x01, .subpage = 0x00, .emulate = spc_modesense_rwrecovery पूर्ण,
	अणु .page = 0x08, .subpage = 0x00, .emulate = spc_modesense_caching पूर्ण,
	अणु .page = 0x0a, .subpage = 0x00, .emulate = spc_modesense_control पूर्ण,
	अणु .page = 0x1c, .subpage = 0x00, .emulate = spc_modesense_inक्रमmational_exceptions पूर्ण,
पूर्ण;

अटल व्योम spc_modesense_ग_लिखो_protect(अचिन्हित अक्षर *buf, पूर्णांक type)
अणु
	/*
	 * I believe that the WP bit (bit 7) in the mode header is the same क्रम
	 * all device types..
	 */
	चयन (type) अणु
	हाल TYPE_DISK:
	हाल TYPE_TAPE:
	शेष:
		buf[0] |= 0x80; /* WP bit */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम spc_modesense_dpofua(अचिन्हित अक्षर *buf, पूर्णांक type)
अणु
	चयन (type) अणु
	हाल TYPE_DISK:
		buf[0] |= 0x10; /* DPOFUA bit */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक spc_modesense_blockdesc(अचिन्हित अक्षर *buf, u64 blocks, u32 block_size)
अणु
	*buf++ = 8;
	put_unaligned_be32(min(blocks, 0xffffffffull), buf);
	buf += 4;
	put_unaligned_be32(block_size, buf);
	वापस 9;
पूर्ण

अटल पूर्णांक spc_modesense_दीर्घ_blockdesc(अचिन्हित अक्षर *buf, u64 blocks, u32 block_size)
अणु
	अगर (blocks <= 0xffffffff)
		वापस spc_modesense_blockdesc(buf + 3, blocks, block_size) + 3;

	*buf++ = 1;		/* LONGLBA */
	buf += 2;
	*buf++ = 16;
	put_unaligned_be64(blocks, buf);
	buf += 12;
	put_unaligned_be32(block_size, buf);

	वापस 17;
पूर्ण

अटल sense_reason_t spc_emulate_modesense(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	अक्षर *cdb = cmd->t_task_cdb;
	अचिन्हित अक्षर buf[SE_MODE_PAGE_BUF], *rbuf;
	पूर्णांक type = dev->transport->get_device_type(dev);
	पूर्णांक ten = (cmd->t_task_cdb[0] == MODE_SENSE_10);
	bool dbd = !!(cdb[1] & 0x08);
	bool llba = ten ? !!(cdb[1] & 0x10) : false;
	u8 pc = cdb[2] >> 6;
	u8 page = cdb[2] & 0x3f;
	u8 subpage = cdb[3];
	पूर्णांक length = 0;
	पूर्णांक ret;
	पूर्णांक i;

	स_रखो(buf, 0, SE_MODE_PAGE_BUF);

	/*
	 * Skip over MODE DATA LENGTH + MEDIUM TYPE fields to byte 3 क्रम
	 * MODE_SENSE_10 and byte 2 क्रम MODE_SENSE (6).
	 */
	length = ten ? 3 : 2;

	/* DEVICE-SPECIFIC PARAMETER */
	अगर (cmd->se_lun->lun_access_ro || target_lun_is_rकरोnly(cmd))
		spc_modesense_ग_लिखो_protect(&buf[length], type);

	/*
	 * SBC only allows us to enable FUA and DPO together.  Fortunately
	 * DPO is explicitly specअगरied as a hपूर्णांक, so a noop is a perfectly
	 * valid implementation.
	 */
	अगर (target_check_fua(dev))
		spc_modesense_dpofua(&buf[length], type);

	++length;

	/* BLOCK DESCRIPTOR */

	/*
	 * For now we only include a block descriptor क्रम disk (SBC)
	 * devices; other command sets use a slightly dअगरferent क्रमmat.
	 */
	अगर (!dbd && type == TYPE_DISK) अणु
		u64 blocks = dev->transport->get_blocks(dev);
		u32 block_size = dev->dev_attrib.block_size;

		अगर (ten) अणु
			अगर (llba) अणु
				length += spc_modesense_दीर्घ_blockdesc(&buf[length],
								       blocks, block_size);
			पूर्ण अन्यथा अणु
				length += 3;
				length += spc_modesense_blockdesc(&buf[length],
								  blocks, block_size);
			पूर्ण
		पूर्ण अन्यथा अणु
			length += spc_modesense_blockdesc(&buf[length], blocks,
							  block_size);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ten)
			length += 4;
		अन्यथा
			length += 1;
	पूर्ण

	अगर (page == 0x3f) अणु
		अगर (subpage != 0x00 && subpage != 0xff) अणु
			pr_warn("MODE_SENSE: Invalid subpage code: 0x%02x\n", subpage);
			वापस TCM_INVALID_CDB_FIELD;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(modesense_handlers); ++i) अणु
			/*
			 * Tricky way to say all subpage 00h क्रम
			 * subpage==0, all subpages क्रम subpage==0xff
			 * (and we just checked above that those are
			 * the only two possibilities).
			 */
			अगर ((modesense_handlers[i].subpage & ~subpage) == 0) अणु
				ret = modesense_handlers[i].emulate(cmd, pc, &buf[length]);
				अगर (!ten && length + ret >= 255)
					अवरोध;
				length += ret;
			पूर्ण
		पूर्ण

		जाओ set_length;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(modesense_handlers); ++i)
		अगर (modesense_handlers[i].page == page &&
		    modesense_handlers[i].subpage == subpage) अणु
			length += modesense_handlers[i].emulate(cmd, pc, &buf[length]);
			जाओ set_length;
		पूर्ण

	/*
	 * We करोn't पूर्णांकend to implement:
	 *  - obsolete page 03h "format parameters" (checked by Solaris)
	 */
	अगर (page != 0x03)
		pr_err("MODE SENSE: unimplemented page/subpage: 0x%02x/0x%02x\n",
		       page, subpage);

	वापस TCM_UNKNOWN_MODE_PAGE;

set_length:
	अगर (ten)
		put_unaligned_be16(length - 2, buf);
	अन्यथा
		buf[0] = length - 1;

	rbuf = transport_kmap_data_sg(cmd);
	अगर (rbuf) अणु
		स_नकल(rbuf, buf, min_t(u32, SE_MODE_PAGE_BUF, cmd->data_length));
		transport_kunmap_data_sg(cmd);
	पूर्ण

	target_complete_cmd_with_length(cmd, GOOD, length);
	वापस 0;
पूर्ण

अटल sense_reason_t spc_emulate_modeselect(काष्ठा se_cmd *cmd)
अणु
	अक्षर *cdb = cmd->t_task_cdb;
	bool ten = cdb[0] == MODE_SELECT_10;
	पूर्णांक off = ten ? 8 : 4;
	bool pf = !!(cdb[1] & 0x10);
	u8 page, subpage;
	अचिन्हित अक्षर *buf;
	अचिन्हित अक्षर tbuf[SE_MODE_PAGE_BUF];
	पूर्णांक length;
	sense_reason_t ret = 0;
	पूर्णांक i;

	अगर (!cmd->data_length) अणु
		target_complete_cmd(cmd, GOOD);
		वापस 0;
	पूर्ण

	अगर (cmd->data_length < off + 2)
		वापस TCM_PARAMETER_LIST_LENGTH_ERROR;

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	अगर (!pf) अणु
		ret = TCM_INVALID_CDB_FIELD;
		जाओ out;
	पूर्ण

	page = buf[off] & 0x3f;
	subpage = buf[off] & 0x40 ? buf[off + 1] : 0;

	क्रम (i = 0; i < ARRAY_SIZE(modesense_handlers); ++i)
		अगर (modesense_handlers[i].page == page &&
		    modesense_handlers[i].subpage == subpage) अणु
			स_रखो(tbuf, 0, SE_MODE_PAGE_BUF);
			length = modesense_handlers[i].emulate(cmd, 0, tbuf);
			जाओ check_contents;
		पूर्ण

	ret = TCM_UNKNOWN_MODE_PAGE;
	जाओ out;

check_contents:
	अगर (cmd->data_length < off + length) अणु
		ret = TCM_PARAMETER_LIST_LENGTH_ERROR;
		जाओ out;
	पूर्ण

	अगर (स_भेद(buf + off, tbuf, length))
		ret = TCM_INVALID_PARAMETER_LIST;

out:
	transport_kunmap_data_sg(cmd);

	अगर (!ret)
		target_complete_cmd(cmd, GOOD);
	वापस ret;
पूर्ण

अटल sense_reason_t spc_emulate_request_sense(काष्ठा se_cmd *cmd)
अणु
	अचिन्हित अक्षर *cdb = cmd->t_task_cdb;
	अचिन्हित अक्षर *rbuf;
	u8 ua_asc = 0, ua_ascq = 0;
	अचिन्हित अक्षर buf[SE_SENSE_BUF];
	bool desc_क्रमmat = target_sense_desc_क्रमmat(cmd->se_dev);

	स_रखो(buf, 0, SE_SENSE_BUF);

	अगर (cdb[1] & 0x01) अणु
		pr_err("REQUEST_SENSE description emulation not"
			" supported\n");
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	rbuf = transport_kmap_data_sg(cmd);
	अगर (!rbuf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	अगर (!core_scsi3_ua_clear_क्रम_request_sense(cmd, &ua_asc, &ua_ascq))
		scsi_build_sense_buffer(desc_क्रमmat, buf, UNIT_ATTENTION,
					ua_asc, ua_ascq);
	अन्यथा
		scsi_build_sense_buffer(desc_क्रमmat, buf, NO_SENSE, 0x0, 0x0);

	स_नकल(rbuf, buf, min_t(u32, माप(buf), cmd->data_length));
	transport_kunmap_data_sg(cmd);

	target_complete_cmd(cmd, GOOD);
	वापस 0;
पूर्ण

sense_reason_t spc_emulate_report_luns(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_dev_entry *deve;
	काष्ठा se_session *sess = cmd->se_sess;
	काष्ठा se_node_acl *nacl;
	काष्ठा scsi_lun slun;
	अचिन्हित अक्षर *buf;
	u32 lun_count = 0, offset = 8;
	__be32 len;

	buf = transport_kmap_data_sg(cmd);
	अगर (cmd->data_length && !buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	/*
	 * If no काष्ठा se_session poपूर्णांकer is present, this काष्ठा se_cmd is
	 * coming via a target_core_mod PASSTHROUGH op, and not through
	 * a $FABRIC_MOD.  In that हाल, report LUN=0 only.
	 */
	अगर (!sess)
		जाओ करोne;

	nacl = sess->se_node_acl;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(deve, &nacl->lun_entry_hlist, link) अणु
		/*
		 * We determine the correct LUN LIST LENGTH even once we
		 * have reached the initial allocation length.
		 * See SPC2-R20 7.19.
		 */
		lun_count++;
		अगर (offset >= cmd->data_length)
			जारी;

		पूर्णांक_to_scsilun(deve->mapped_lun, &slun);
		स_नकल(buf + offset, &slun,
		       min(8u, cmd->data_length - offset));
		offset += 8;
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * See SPC3 r07, page 159.
	 */
करोne:
	/*
	 * If no LUNs are accessible, report भव LUN 0.
	 */
	अगर (lun_count == 0) अणु
		पूर्णांक_to_scsilun(0, &slun);
		अगर (cmd->data_length > 8)
			स_नकल(buf + offset, &slun,
			       min(8u, cmd->data_length - offset));
		lun_count = 1;
	पूर्ण

	अगर (buf) अणु
		len = cpu_to_be32(lun_count * 8);
		स_नकल(buf, &len, min_t(पूर्णांक, माप len, cmd->data_length));
		transport_kunmap_data_sg(cmd);
	पूर्ण

	target_complete_cmd_with_length(cmd, GOOD, 8 + lun_count * 8);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(spc_emulate_report_luns);

अटल sense_reason_t
spc_emulate_testunitपढ़ोy(काष्ठा se_cmd *cmd)
अणु
	target_complete_cmd(cmd, GOOD);
	वापस 0;
पूर्ण

sense_reason_t
spc_parse_cdb(काष्ठा se_cmd *cmd, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित अक्षर *cdb = cmd->t_task_cdb;

	अगर (!dev->dev_attrib.emulate_pr &&
	    ((cdb[0] == PERSISTENT_RESERVE_IN) ||
	     (cdb[0] == PERSISTENT_RESERVE_OUT) ||
	     (cdb[0] == RELEASE || cdb[0] == RELEASE_10) ||
	     (cdb[0] == RESERVE || cdb[0] == RESERVE_10))) अणु
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;
	पूर्ण

	चयन (cdb[0]) अणु
	हाल MODE_SELECT:
		*size = cdb[4];
		cmd->execute_cmd = spc_emulate_modeselect;
		अवरोध;
	हाल MODE_SELECT_10:
		*size = get_unaligned_be16(&cdb[7]);
		cmd->execute_cmd = spc_emulate_modeselect;
		अवरोध;
	हाल MODE_SENSE:
		*size = cdb[4];
		cmd->execute_cmd = spc_emulate_modesense;
		अवरोध;
	हाल MODE_SENSE_10:
		*size = get_unaligned_be16(&cdb[7]);
		cmd->execute_cmd = spc_emulate_modesense;
		अवरोध;
	हाल LOG_SELECT:
	हाल LOG_SENSE:
		*size = get_unaligned_be16(&cdb[7]);
		अवरोध;
	हाल PERSISTENT_RESERVE_IN:
		*size = get_unaligned_be16(&cdb[7]);
		cmd->execute_cmd = target_scsi3_emulate_pr_in;
		अवरोध;
	हाल PERSISTENT_RESERVE_OUT:
		*size = get_unaligned_be32(&cdb[5]);
		cmd->execute_cmd = target_scsi3_emulate_pr_out;
		अवरोध;
	हाल RELEASE:
	हाल RELEASE_10:
		अगर (cdb[0] == RELEASE_10)
			*size = get_unaligned_be16(&cdb[7]);
		अन्यथा
			*size = cmd->data_length;

		cmd->execute_cmd = target_scsi2_reservation_release;
		अवरोध;
	हाल RESERVE:
	हाल RESERVE_10:
		/*
		 * The SPC-2 RESERVE करोes not contain a size in the SCSI CDB.
		 * Assume the passthrough or $FABRIC_MOD will tell us about it.
		 */
		अगर (cdb[0] == RESERVE_10)
			*size = get_unaligned_be16(&cdb[7]);
		अन्यथा
			*size = cmd->data_length;

		cmd->execute_cmd = target_scsi2_reservation_reserve;
		अवरोध;
	हाल REQUEST_SENSE:
		*size = cdb[4];
		cmd->execute_cmd = spc_emulate_request_sense;
		अवरोध;
	हाल INQUIRY:
		*size = get_unaligned_be16(&cdb[3]);

		/*
		 * Do implicit HEAD_OF_QUEUE processing क्रम INQUIRY.
		 * See spc4r17 section 5.3
		 */
		cmd->sam_task_attr = TCM_HEAD_TAG;
		cmd->execute_cmd = spc_emulate_inquiry;
		अवरोध;
	हाल SECURITY_PROTOCOL_IN:
	हाल SECURITY_PROTOCOL_OUT:
		*size = get_unaligned_be32(&cdb[6]);
		अवरोध;
	हाल EXTENDED_COPY:
		*size = get_unaligned_be32(&cdb[10]);
		cmd->execute_cmd = target_करो_xcopy;
		अवरोध;
	हाल RECEIVE_COPY_RESULTS:
		*size = get_unaligned_be32(&cdb[10]);
		cmd->execute_cmd = target_करो_receive_copy_results;
		अवरोध;
	हाल READ_ATTRIBUTE:
	हाल WRITE_ATTRIBUTE:
		*size = get_unaligned_be32(&cdb[10]);
		अवरोध;
	हाल RECEIVE_DIAGNOSTIC:
	हाल SEND_DIAGNOSTIC:
		*size = get_unaligned_be16(&cdb[3]);
		अवरोध;
	हाल WRITE_BUFFER:
		*size = get_unaligned_be24(&cdb[6]);
		अवरोध;
	हाल REPORT_LUNS:
		cmd->execute_cmd = spc_emulate_report_luns;
		*size = get_unaligned_be32(&cdb[6]);
		/*
		 * Do implicit HEAD_OF_QUEUE processing क्रम REPORT_LUNS
		 * See spc4r17 section 5.3
		 */
		cmd->sam_task_attr = TCM_HEAD_TAG;
		अवरोध;
	हाल TEST_UNIT_READY:
		cmd->execute_cmd = spc_emulate_testunitपढ़ोy;
		*size = 0;
		अवरोध;
	हाल MAINTEन_अंकCE_IN:
		अगर (dev->transport->get_device_type(dev) != TYPE_ROM) अणु
			/*
			 * MAINTEन_अंकCE_IN from SCC-2
			 * Check क्रम emulated MI_REPORT_TARGET_PGS
			 */
			अगर ((cdb[1] & 0x1f) == MI_REPORT_TARGET_PGS) अणु
				cmd->execute_cmd =
					target_emulate_report_target_port_groups;
			पूर्ण
			*size = get_unaligned_be32(&cdb[6]);
		पूर्ण अन्यथा अणु
			/*
			 * GPCMD_SEND_KEY from multi media commands
			 */
			*size = get_unaligned_be16(&cdb[8]);
		पूर्ण
		अवरोध;
	हाल MAINTEन_अंकCE_OUT:
		अगर (dev->transport->get_device_type(dev) != TYPE_ROM) अणु
			/*
			 * MAINTEन_अंकCE_OUT from SCC-2
			 * Check क्रम emulated MO_SET_TARGET_PGS.
			 */
			अगर (cdb[1] == MO_SET_TARGET_PGS) अणु
				cmd->execute_cmd =
					target_emulate_set_target_port_groups;
			पूर्ण
			*size = get_unaligned_be32(&cdb[6]);
		पूर्ण अन्यथा अणु
			/*
			 * GPCMD_SEND_KEY from multi media commands
			 */
			*size = get_unaligned_be16(&cdb[8]);
		पूर्ण
		अवरोध;
	शेष:
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(spc_parse_cdb);
