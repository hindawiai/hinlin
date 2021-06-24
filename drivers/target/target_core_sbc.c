<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SCSI Block Commands (SBC) parsing and emulation.
 *
 * (c) Copyright 2002-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/crc-t10dअगर.h>
#समावेश <linux/t10-pi.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_ua.h"
#समावेश "target_core_alua.h"

अटल sense_reason_t
sbc_check_prot(काष्ठा se_device *, काष्ठा se_cmd *, अचिन्हित अक्षर *, u32, bool);
अटल sense_reason_t sbc_execute_unmap(काष्ठा se_cmd *cmd);

अटल sense_reason_t
sbc_emulate_पढ़ोcapacity(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित अक्षर *cdb = cmd->t_task_cdb;
	अचिन्हित दीर्घ दीर्घ blocks_दीर्घ = dev->transport->get_blocks(dev);
	अचिन्हित अक्षर *rbuf;
	अचिन्हित अक्षर buf[8];
	u32 blocks;

	/*
	 * SBC-2 says:
	 *   If the PMI bit is set to zero and the LOGICAL BLOCK
	 *   ADDRESS field is not set to zero, the device server shall
	 *   terminate the command with CHECK CONDITION status with
	 *   the sense key set to ILLEGAL REQUEST and the additional
	 *   sense code set to INVALID FIELD IN CDB.
	 *
	 * In SBC-3, these fields are obsolete, but some SCSI
	 * compliance tests actually check this, so we might as well
	 * follow SBC-2.
	 */
	अगर (!(cdb[8] & 1) && !!(cdb[2] | cdb[3] | cdb[4] | cdb[5]))
		वापस TCM_INVALID_CDB_FIELD;

	अगर (blocks_दीर्घ >= 0x00000000ffffffff)
		blocks = 0xffffffff;
	अन्यथा
		blocks = (u32)blocks_दीर्घ;

	put_unaligned_be32(blocks, &buf[0]);
	put_unaligned_be32(dev->dev_attrib.block_size, &buf[4]);

	rbuf = transport_kmap_data_sg(cmd);
	अगर (rbuf) अणु
		स_नकल(rbuf, buf, min_t(u32, माप(buf), cmd->data_length));
		transport_kunmap_data_sg(cmd);
	पूर्ण

	target_complete_cmd_with_length(cmd, GOOD, 8);
	वापस 0;
पूर्ण

अटल sense_reason_t
sbc_emulate_पढ़ोcapacity_16(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *sess = cmd->se_sess;
	पूर्णांक pi_prot_type = dev->dev_attrib.pi_prot_type;

	अचिन्हित अक्षर *rbuf;
	अचिन्हित अक्षर buf[32];
	अचिन्हित दीर्घ दीर्घ blocks = dev->transport->get_blocks(dev);

	स_रखो(buf, 0, माप(buf));
	put_unaligned_be64(blocks, &buf[0]);
	put_unaligned_be32(dev->dev_attrib.block_size, &buf[8]);
	/*
	 * Set P_TYPE and PROT_EN bits क्रम DIF support
	 */
	अगर (sess->sup_prot_ops & (TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS)) अणु
		/*
		 * Only override a device's pi_prot_type अगर no T10-PI is
		 * available, and sess_prot_type has been explicitly enabled.
		 */
		अगर (!pi_prot_type)
			pi_prot_type = sess->sess_prot_type;

		अगर (pi_prot_type)
			buf[12] = (pi_prot_type - 1) << 1 | 0x1;
	पूर्ण

	अगर (dev->transport->get_lbppbe)
		buf[13] = dev->transport->get_lbppbe(dev) & 0x0f;

	अगर (dev->transport->get_alignment_offset_lbas) अणु
		u16 lalba = dev->transport->get_alignment_offset_lbas(dev);

		put_unaligned_be16(lalba, &buf[14]);
	पूर्ण

	/*
	 * Set Thin Provisioning Enable bit following sbc3r22 in section
	 * READ CAPACITY (16) byte 14 अगर emulate_tpu or emulate_tpws is enabled.
	 */
	अगर (dev->dev_attrib.emulate_tpu || dev->dev_attrib.emulate_tpws) अणु
		buf[14] |= 0x80;

		/*
		 * LBPRZ signअगरies that zeroes will be पढ़ो back from an LBA after
		 * an UNMAP or WRITE SAME w/ unmap bit (sbc3r36 5.16.2)
		 */
		अगर (dev->dev_attrib.unmap_zeroes_data)
			buf[14] |= 0x40;
	पूर्ण

	rbuf = transport_kmap_data_sg(cmd);
	अगर (rbuf) अणु
		स_नकल(rbuf, buf, min_t(u32, माप(buf), cmd->data_length));
		transport_kunmap_data_sg(cmd);
	पूर्ण

	target_complete_cmd_with_length(cmd, GOOD, 32);
	वापस 0;
पूर्ण

अटल sense_reason_t
sbc_emulate_startstop(काष्ठा se_cmd *cmd)
अणु
	अचिन्हित अक्षर *cdb = cmd->t_task_cdb;

	/*
	 * See sbc3r36 section 5.25
	 * Immediate bit should be set since there is nothing to complete
	 * POWER CONDITION MODIFIER 0h
	 */
	अगर (!(cdb[1] & 1) || cdb[2] || cdb[3])
		वापस TCM_INVALID_CDB_FIELD;

	/*
	 * See sbc3r36 section 5.25
	 * POWER CONDITION 0h START_VALID - process START and LOEJ
	 */
	अगर (cdb[4] >> 4 & 0xf)
		वापस TCM_INVALID_CDB_FIELD;

	/*
	 * See sbc3r36 section 5.25
	 * LOEJ 0h - nothing to load or unload
	 * START 1h - we are पढ़ोy
	 */
	अगर (!(cdb[4] & 1) || (cdb[4] & 2) || (cdb[4] & 4))
		वापस TCM_INVALID_CDB_FIELD;

	target_complete_cmd(cmd, SAM_STAT_GOOD);
	वापस 0;
पूर्ण

sector_t sbc_get_ग_लिखो_same_sectors(काष्ठा se_cmd *cmd)
अणु
	u32 num_blocks;

	अगर (cmd->t_task_cdb[0] == WRITE_SAME)
		num_blocks = get_unaligned_be16(&cmd->t_task_cdb[7]);
	अन्यथा अगर (cmd->t_task_cdb[0] == WRITE_SAME_16)
		num_blocks = get_unaligned_be32(&cmd->t_task_cdb[10]);
	अन्यथा /* WRITE_SAME_32 via VARIABLE_LENGTH_CMD */
		num_blocks = get_unaligned_be32(&cmd->t_task_cdb[28]);

	/*
	 * Use the explicit range when non zero is supplied, otherwise calculate
	 * the reमुख्यing range based on ->get_blocks() - starting LBA.
	 */
	अगर (num_blocks)
		वापस num_blocks;

	वापस cmd->se_dev->transport->get_blocks(cmd->se_dev) -
		cmd->t_task_lba + 1;
पूर्ण
EXPORT_SYMBOL(sbc_get_ग_लिखो_same_sectors);

अटल sense_reason_t
sbc_execute_ग_लिखो_same_unmap(काष्ठा se_cmd *cmd)
अणु
	काष्ठा sbc_ops *ops = cmd->protocol_data;
	sector_t nolb = sbc_get_ग_लिखो_same_sectors(cmd);
	sense_reason_t ret;

	अगर (nolb) अणु
		ret = ops->execute_unmap(cmd, cmd->t_task_lba, nolb);
		अगर (ret)
			वापस ret;
	पूर्ण

	target_complete_cmd(cmd, GOOD);
	वापस 0;
पूर्ण

अटल sense_reason_t
sbc_emulate_noop(काष्ठा se_cmd *cmd)
अणु
	target_complete_cmd(cmd, GOOD);
	वापस 0;
पूर्ण

अटल अंतरभूत u32 sbc_get_size(काष्ठा se_cmd *cmd, u32 sectors)
अणु
	वापस cmd->se_dev->dev_attrib.block_size * sectors;
पूर्ण

अटल अंतरभूत u32 transport_get_sectors_6(अचिन्हित अक्षर *cdb)
अणु
	/*
	 * Use 8-bit sector value.  SBC-3 says:
	 *
	 *   A TRANSFER LENGTH field set to zero specअगरies that 256
	 *   logical blocks shall be written.  Any other value
	 *   specअगरies the number of logical blocks that shall be
	 *   written.
	 */
	वापस cdb[4] ? : 256;
पूर्ण

अटल अंतरभूत u32 transport_get_sectors_10(अचिन्हित अक्षर *cdb)
अणु
	वापस get_unaligned_be16(&cdb[7]);
पूर्ण

अटल अंतरभूत u32 transport_get_sectors_12(अचिन्हित अक्षर *cdb)
अणु
	वापस get_unaligned_be32(&cdb[6]);
पूर्ण

अटल अंतरभूत u32 transport_get_sectors_16(अचिन्हित अक्षर *cdb)
अणु
	वापस get_unaligned_be32(&cdb[10]);
पूर्ण

/*
 * Used क्रम VARIABLE_LENGTH_CDB WRITE_32 and READ_32 variants
 */
अटल अंतरभूत u32 transport_get_sectors_32(अचिन्हित अक्षर *cdb)
अणु
	वापस get_unaligned_be32(&cdb[28]);

पूर्ण

अटल अंतरभूत u32 transport_lba_21(अचिन्हित अक्षर *cdb)
अणु
	वापस get_unaligned_be24(&cdb[1]) & 0x1fffff;
पूर्ण

अटल अंतरभूत u32 transport_lba_32(अचिन्हित अक्षर *cdb)
अणु
	वापस get_unaligned_be32(&cdb[2]);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ transport_lba_64(अचिन्हित अक्षर *cdb)
अणु
	वापस get_unaligned_be64(&cdb[2]);
पूर्ण

/*
 * For VARIABLE_LENGTH_CDB w/ 32 byte extended CDBs
 */
अटल अंतरभूत अचिन्हित दीर्घ दीर्घ transport_lba_64_ext(अचिन्हित अक्षर *cdb)
अणु
	वापस get_unaligned_be64(&cdb[12]);
पूर्ण

अटल sense_reason_t
sbc_setup_ग_लिखो_same(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *flags, काष्ठा sbc_ops *ops)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	sector_t end_lba = dev->transport->get_blocks(dev) + 1;
	अचिन्हित पूर्णांक sectors = sbc_get_ग_लिखो_same_sectors(cmd);
	sense_reason_t ret;

	अगर ((flags[0] & 0x04) || (flags[0] & 0x02)) अणु
		pr_err("WRITE_SAME PBDATA and LBDATA"
			" bits not supported for Block Discard"
			" Emulation\n");
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;
	पूर्ण
	अगर (sectors > cmd->se_dev->dev_attrib.max_ग_लिखो_same_len) अणु
		pr_warn("WRITE_SAME sectors: %u exceeds max_write_same_len: %u\n",
			sectors, cmd->se_dev->dev_attrib.max_ग_लिखो_same_len);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण
	/*
	 * Sanity check क्रम LBA wrap and request past end of device.
	 */
	अगर (((cmd->t_task_lba + sectors) < cmd->t_task_lba) ||
	    ((cmd->t_task_lba + sectors) > end_lba)) अणु
		pr_err("WRITE_SAME exceeds last lba %llu (lba %llu, sectors %u)\n",
		       (अचिन्हित दीर्घ दीर्घ)end_lba, cmd->t_task_lba, sectors);
		वापस TCM_ADDRESS_OUT_OF_RANGE;
	पूर्ण

	/* We always have ANC_SUP == 0 so setting ANCHOR is always an error */
	अगर (flags[0] & 0x10) अणु
		pr_warn("WRITE SAME with ANCHOR not supported\n");
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण
	/*
	 * Special हाल क्रम WRITE_SAME w/ UNMAP=1 that ends up getting
	 * translated पूर्णांकo block discard requests within backend code.
	 */
	अगर (flags[0] & 0x08) अणु
		अगर (!ops->execute_unmap)
			वापस TCM_UNSUPPORTED_SCSI_OPCODE;

		अगर (!dev->dev_attrib.emulate_tpws) अणु
			pr_err("Got WRITE_SAME w/ UNMAP=1, but backend device"
			       " has emulate_tpws disabled\n");
			वापस TCM_UNSUPPORTED_SCSI_OPCODE;
		पूर्ण
		cmd->execute_cmd = sbc_execute_ग_लिखो_same_unmap;
		वापस 0;
	पूर्ण
	अगर (!ops->execute_ग_लिखो_same)
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;

	ret = sbc_check_prot(dev, cmd, &cmd->t_task_cdb[0], sectors, true);
	अगर (ret)
		वापस ret;

	cmd->execute_cmd = ops->execute_ग_लिखो_same;
	वापस 0;
पूर्ण

अटल sense_reason_t xdपढ़ोग_लिखो_callback(काष्ठा se_cmd *cmd, bool success,
					   पूर्णांक *post_ret)
अणु
	अचिन्हित अक्षर *buf, *addr;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक offset;
	sense_reason_t ret = TCM_NO_SENSE;
	पूर्णांक i, count;

	अगर (!success)
		वापस 0;

	/*
	 * From sbc3r22.pdf section 5.48 XDWRITEREAD (10) command
	 *
	 * 1) पढ़ो the specअगरied logical block(s);
	 * 2) transfer logical blocks from the data-out buffer;
	 * 3) XOR the logical blocks transferred from the data-out buffer with
	 *    the logical blocks पढ़ो, storing the resulting XOR data in a buffer;
	 * 4) अगर the DISABLE WRITE bit is set to zero, then ग_लिखो the logical
	 *    blocks transferred from the data-out buffer; and
	 * 5) transfer the resulting XOR data to the data-in buffer.
	 */
	buf = kदो_स्मृति(cmd->data_length, GFP_KERNEL);
	अगर (!buf) अणु
		pr_err("Unable to allocate xor_callback buf\n");
		वापस TCM_OUT_OF_RESOURCES;
	पूर्ण
	/*
	 * Copy the scatterlist WRITE buffer located at cmd->t_data_sg
	 * पूर्णांकo the locally allocated *buf
	 */
	sg_copy_to_buffer(cmd->t_data_sg,
			  cmd->t_data_nents,
			  buf,
			  cmd->data_length);

	/*
	 * Now perक्रमm the XOR against the BIDI पढ़ो memory located at
	 * cmd->t_mem_bidi_list
	 */

	offset = 0;
	क्रम_each_sg(cmd->t_bidi_data_sg, sg, cmd->t_bidi_data_nents, count) अणु
		addr = kmap_atomic(sg_page(sg));
		अगर (!addr) अणु
			ret = TCM_OUT_OF_RESOURCES;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < sg->length; i++)
			*(addr + sg->offset + i) ^= *(buf + offset + i);

		offset += sg->length;
		kunmap_atomic(addr);
	पूर्ण

out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sense_reason_t
sbc_execute_rw(काष्ठा se_cmd *cmd)
अणु
	काष्ठा sbc_ops *ops = cmd->protocol_data;

	वापस ops->execute_rw(cmd, cmd->t_data_sg, cmd->t_data_nents,
			       cmd->data_direction);
पूर्ण

अटल sense_reason_t compare_and_ग_लिखो_post(काष्ठा se_cmd *cmd, bool success,
					     पूर्णांक *post_ret)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	sense_reason_t ret = TCM_NO_SENSE;

	spin_lock_irq(&cmd->t_state_lock);
	अगर (success) अणु
		*post_ret = 1;

		अगर (cmd->scsi_status == SAM_STAT_CHECK_CONDITION)
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	spin_unlock_irq(&cmd->t_state_lock);

	/*
	 * Unlock ->caw_sem originally obtained during sbc_compare_and_ग_लिखो()
	 * beक्रमe the original READ I/O submission.
	 */
	up(&dev->caw_sem);

	वापस ret;
पूर्ण

/*
 * compare @cmp_len bytes of @पढ़ो_sgl with @cmp_sgl. On miscompare, fill
 * @miscmp_off and वापस TCM_MISCOMPARE_VERIFY.
 */
अटल sense_reason_t
compare_and_ग_लिखो_करो_cmp(काष्ठा scatterlist *पढ़ो_sgl, अचिन्हित पूर्णांक पढ़ो_nents,
			 काष्ठा scatterlist *cmp_sgl, अचिन्हित पूर्णांक cmp_nents,
			 अचिन्हित पूर्णांक cmp_len, अचिन्हित पूर्णांक *miscmp_off)
अणु
	अचिन्हित अक्षर *buf = शून्य;
	काष्ठा scatterlist *sg;
	sense_reason_t ret;
	अचिन्हित पूर्णांक offset;
	माप_प्रकार rc;
	पूर्णांक sg_cnt;

	buf = kzalloc(cmp_len, GFP_KERNEL);
	अगर (!buf) अणु
		ret = TCM_OUT_OF_RESOURCES;
		जाओ out;
	पूर्ण

	rc = sg_copy_to_buffer(cmp_sgl, cmp_nents, buf, cmp_len);
	अगर (!rc) अणु
		pr_err("sg_copy_to_buffer() failed for compare_and_write\n");
		ret = TCM_OUT_OF_RESOURCES;
		जाओ out;
	पूर्ण
	/*
	 * Compare SCSI READ payload against verअगरy payload
	 */
	offset = 0;
	ret = TCM_NO_SENSE;
	क्रम_each_sg(पढ़ो_sgl, sg, पढ़ो_nents, sg_cnt) अणु
		अचिन्हित पूर्णांक len = min(sg->length, cmp_len);
		अचिन्हित अक्षर *addr = kmap_atomic(sg_page(sg));

		अगर (स_भेद(addr, buf + offset, len)) अणु
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < len && addr[i] == buf[offset + i]; i++)
				;
			*miscmp_off = offset + i;
			pr_warn("Detected MISCOMPARE at offset %u\n",
				*miscmp_off);
			ret = TCM_MISCOMPARE_VERIFY;
		पूर्ण
		kunmap_atomic(addr);
		अगर (ret != TCM_NO_SENSE)
			जाओ out;

		offset += len;
		cmp_len -= len;
		अगर (!cmp_len)
			अवरोध;
	पूर्ण
	pr_debug("COMPARE AND WRITE read data matches compare data\n");
out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sense_reason_t compare_and_ग_लिखो_callback(काष्ठा se_cmd *cmd, bool success,
						 पूर्णांक *post_ret)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा sg_table ग_लिखो_tbl = अणु पूर्ण;
	काष्ठा scatterlist *ग_लिखो_sg;
	काष्ठा sg_mapping_iter m;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक block_size = dev->dev_attrib.block_size;
	अचिन्हित पूर्णांक compare_len = (cmd->t_task_nolb * block_size);
	अचिन्हित पूर्णांक miscmp_off = 0;
	sense_reason_t ret = TCM_NO_SENSE;
	पूर्णांक i;

	/*
	 * Handle early failure in transport_generic_request_failure(),
	 * which will not have taken ->caw_sem yet..
	 */
	अगर (!success && (!cmd->t_data_sg || !cmd->t_bidi_data_sg))
		वापस TCM_NO_SENSE;
	/*
	 * Handle special हाल क्रम zero-length COMPARE_AND_WRITE
	 */
	अगर (!cmd->data_length)
		जाओ out;
	/*
	 * Immediately निकास + release dev->caw_sem अगर command has alपढ़ोy
	 * been failed with a non-zero SCSI status.
	 */
	अगर (cmd->scsi_status) अणु
		pr_debug("compare_and_write_callback: non zero scsi_status:"
			" 0x%02x\n", cmd->scsi_status);
		*post_ret = 1;
		अगर (cmd->scsi_status == SAM_STAT_CHECK_CONDITION)
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		जाओ out;
	पूर्ण

	ret = compare_and_ग_लिखो_करो_cmp(cmd->t_bidi_data_sg,
				       cmd->t_bidi_data_nents,
				       cmd->t_data_sg,
				       cmd->t_data_nents,
				       compare_len,
				       &miscmp_off);
	अगर (ret == TCM_MISCOMPARE_VERIFY) अणु
		/*
		 * SBC-4 r15: 5.3 COMPARE AND WRITE command
		 * In the sense data (see 4.18 and SPC-5) the offset from the
		 * start of the Data-Out Buffer to the first byte of data that
		 * was not equal shall be reported in the INFORMATION field.
		 */
		cmd->sense_info = miscmp_off;
		जाओ out;
	पूर्ण अन्यथा अगर (ret)
		जाओ out;

	अगर (sg_alloc_table(&ग_लिखो_tbl, cmd->t_data_nents, GFP_KERNEL) < 0) अणु
		pr_err("Unable to allocate compare_and_write sg\n");
		ret = TCM_OUT_OF_RESOURCES;
		जाओ out;
	पूर्ण
	ग_लिखो_sg = ग_लिखो_tbl.sgl;

	i = 0;
	len = compare_len;
	sg_miter_start(&m, cmd->t_data_sg, cmd->t_data_nents, SG_MITER_TO_SG);
	/*
	 * Currently assumes NoLB=1 and SGLs are PAGE_SIZE..
	 */
	जबतक (len) अणु
		sg_miter_next(&m);

		अगर (block_size < PAGE_SIZE) अणु
			sg_set_page(&ग_लिखो_sg[i], m.page, block_size,
				    m.piter.sg->offset + block_size);
		पूर्ण अन्यथा अणु
			sg_miter_next(&m);
			sg_set_page(&ग_लिखो_sg[i], m.page, block_size,
				    m.piter.sg->offset);
		पूर्ण
		len -= block_size;
		i++;
	पूर्ण
	sg_miter_stop(&m);
	/*
	 * Save the original SGL + nents values beक्रमe updating to new
	 * assignments, to be released in transport_मुक्त_pages() ->
	 * transport_reset_sgl_orig()
	 */
	cmd->t_data_sg_orig = cmd->t_data_sg;
	cmd->t_data_sg = ग_लिखो_sg;
	cmd->t_data_nents_orig = cmd->t_data_nents;
	cmd->t_data_nents = 1;

	cmd->sam_task_attr = TCM_HEAD_TAG;
	cmd->transport_complete_callback = compare_and_ग_लिखो_post;
	/*
	 * Now reset ->execute_cmd() to the normal sbc_execute_rw() handler
	 * क्रम submitting the adjusted SGL to ग_लिखो instance user-data.
	 */
	cmd->execute_cmd = sbc_execute_rw;

	spin_lock_irq(&cmd->t_state_lock);
	cmd->t_state = TRANSPORT_PROCESSING;
	cmd->transport_state |= CMD_T_ACTIVE | CMD_T_SENT;
	spin_unlock_irq(&cmd->t_state_lock);

	__target_execute_cmd(cmd, false);

	वापस ret;

out:
	/*
	 * In the MISCOMPARE or failure हाल, unlock ->caw_sem obtained in
	 * sbc_compare_and_ग_लिखो() beक्रमe the original READ I/O submission.
	 */
	up(&dev->caw_sem);
	sg_मुक्त_table(&ग_लिखो_tbl);
	वापस ret;
पूर्ण

अटल sense_reason_t
sbc_compare_and_ग_लिखो(काष्ठा se_cmd *cmd)
अणु
	काष्ठा sbc_ops *ops = cmd->protocol_data;
	काष्ठा se_device *dev = cmd->se_dev;
	sense_reason_t ret;
	पूर्णांक rc;
	/*
	 * Submit the READ first क्रम COMPARE_AND_WRITE to perक्रमm the
	 * comparision using SGLs at cmd->t_bidi_data_sg..
	 */
	rc = करोwn_पूर्णांकerruptible(&dev->caw_sem);
	अगर (rc != 0) अणु
		cmd->transport_complete_callback = शून्य;
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	/*
	 * Reset cmd->data_length to inभागidual block_size in order to not
	 * confuse backend drivers that depend on this value matching the
	 * size of the I/O being submitted.
	 */
	cmd->data_length = cmd->t_task_nolb * dev->dev_attrib.block_size;

	ret = ops->execute_rw(cmd, cmd->t_bidi_data_sg, cmd->t_bidi_data_nents,
			      DMA_FROM_DEVICE);
	अगर (ret) अणु
		cmd->transport_complete_callback = शून्य;
		up(&dev->caw_sem);
		वापस ret;
	पूर्ण
	/*
	 * Unlock of dev->caw_sem to occur in compare_and_ग_लिखो_callback()
	 * upon MISCOMPARE, or in compare_and_ग_लिखो_करोne() upon completion
	 * of WRITE instance user-data.
	 */
	वापस TCM_NO_SENSE;
पूर्ण

अटल पूर्णांक
sbc_set_prot_op_checks(u8 protect, bool fabric_prot, क्रमागत target_prot_type prot_type,
		       bool is_ग_लिखो, काष्ठा se_cmd *cmd)
अणु
	अगर (is_ग_लिखो) अणु
		cmd->prot_op = fabric_prot ? TARGET_PROT_DOUT_STRIP :
			       protect ? TARGET_PROT_DOUT_PASS :
			       TARGET_PROT_DOUT_INSERT;
		चयन (protect) अणु
		हाल 0x0:
		हाल 0x3:
			cmd->prot_checks = 0;
			अवरोध;
		हाल 0x1:
		हाल 0x5:
			cmd->prot_checks = TARGET_DIF_CHECK_GUARD;
			अगर (prot_type == TARGET_DIF_TYPE1_PROT)
				cmd->prot_checks |= TARGET_DIF_CHECK_REFTAG;
			अवरोध;
		हाल 0x2:
			अगर (prot_type == TARGET_DIF_TYPE1_PROT)
				cmd->prot_checks = TARGET_DIF_CHECK_REFTAG;
			अवरोध;
		हाल 0x4:
			cmd->prot_checks = TARGET_DIF_CHECK_GUARD;
			अवरोध;
		शेष:
			pr_err("Unsupported protect field %d\n", protect);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		cmd->prot_op = fabric_prot ? TARGET_PROT_DIN_INSERT :
			       protect ? TARGET_PROT_DIN_PASS :
			       TARGET_PROT_DIN_STRIP;
		चयन (protect) अणु
		हाल 0x0:
		हाल 0x1:
		हाल 0x5:
			cmd->prot_checks = TARGET_DIF_CHECK_GUARD;
			अगर (prot_type == TARGET_DIF_TYPE1_PROT)
				cmd->prot_checks |= TARGET_DIF_CHECK_REFTAG;
			अवरोध;
		हाल 0x2:
			अगर (prot_type == TARGET_DIF_TYPE1_PROT)
				cmd->prot_checks = TARGET_DIF_CHECK_REFTAG;
			अवरोध;
		हाल 0x3:
			cmd->prot_checks = 0;
			अवरोध;
		हाल 0x4:
			cmd->prot_checks = TARGET_DIF_CHECK_GUARD;
			अवरोध;
		शेष:
			pr_err("Unsupported protect field %d\n", protect);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sense_reason_t
sbc_check_prot(काष्ठा se_device *dev, काष्ठा se_cmd *cmd, अचिन्हित अक्षर *cdb,
	       u32 sectors, bool is_ग_लिखो)
अणु
	u8 protect = cdb[1] >> 5;
	पूर्णांक sp_ops = cmd->se_sess->sup_prot_ops;
	पूर्णांक pi_prot_type = dev->dev_attrib.pi_prot_type;
	bool fabric_prot = false;

	अगर (!cmd->t_prot_sg || !cmd->t_prot_nents) अणु
		अगर (unlikely(protect &&
		    !dev->dev_attrib.pi_prot_type && !cmd->se_sess->sess_prot_type)) अणु
			pr_err("CDB contains protect bit, but device + fabric does"
			       " not advertise PROTECT=1 feature bit\n");
			वापस TCM_INVALID_CDB_FIELD;
		पूर्ण
		अगर (cmd->prot_pto)
			वापस TCM_NO_SENSE;
	पूर्ण

	चयन (dev->dev_attrib.pi_prot_type) अणु
	हाल TARGET_DIF_TYPE3_PROT:
		cmd->reftag_seed = 0xffffffff;
		अवरोध;
	हाल TARGET_DIF_TYPE2_PROT:
		अगर (protect)
			वापस TCM_INVALID_CDB_FIELD;

		cmd->reftag_seed = cmd->t_task_lba;
		अवरोध;
	हाल TARGET_DIF_TYPE1_PROT:
		cmd->reftag_seed = cmd->t_task_lba;
		अवरोध;
	हाल TARGET_DIF_TYPE0_PROT:
		/*
		 * See अगर the fabric supports T10-PI, and the session has been
		 * configured to allow export PROTECT=1 feature bit with backend
		 * devices that करोn't support T10-PI.
		 */
		fabric_prot = is_ग_लिखो ?
			      !!(sp_ops & (TARGET_PROT_DOUT_PASS | TARGET_PROT_DOUT_STRIP)) :
			      !!(sp_ops & (TARGET_PROT_DIN_PASS | TARGET_PROT_DIN_INSERT));

		अगर (fabric_prot && cmd->se_sess->sess_prot_type) अणु
			pi_prot_type = cmd->se_sess->sess_prot_type;
			अवरोध;
		पूर्ण
		अगर (!protect)
			वापस TCM_NO_SENSE;
		fallthrough;
	शेष:
		pr_err("Unable to determine pi_prot_type for CDB: 0x%02x "
		       "PROTECT: 0x%02x\n", cdb[0], protect);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	अगर (sbc_set_prot_op_checks(protect, fabric_prot, pi_prot_type, is_ग_लिखो, cmd))
		वापस TCM_INVALID_CDB_FIELD;

	cmd->prot_type = pi_prot_type;
	cmd->prot_length = dev->prot_length * sectors;

	/**
	 * In हाल protection inक्रमmation exists over the wire
	 * we modअगरy command data length to describe pure data.
	 * The actual transfer length is data length + protection
	 * length
	 **/
	अगर (protect)
		cmd->data_length = sectors * dev->dev_attrib.block_size;

	pr_debug("%s: prot_type=%d, data_length=%d, prot_length=%d "
		 "prot_op=%d prot_checks=%d\n",
		 __func__, cmd->prot_type, cmd->data_length, cmd->prot_length,
		 cmd->prot_op, cmd->prot_checks);

	वापस TCM_NO_SENSE;
पूर्ण

अटल पूर्णांक
sbc_check_dpofua(काष्ठा se_device *dev, काष्ठा se_cmd *cmd, अचिन्हित अक्षर *cdb)
अणु
	अगर (cdb[1] & 0x10) अणु
		/* see explanation in spc_emulate_modesense */
		अगर (!target_check_fua(dev)) अणु
			pr_err("Got CDB: 0x%02x with DPO bit set, but device"
			       " does not advertise support for DPO\n", cdb[0]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (cdb[1] & 0x8) अणु
		अगर (!target_check_fua(dev)) अणु
			pr_err("Got CDB: 0x%02x with FUA bit set, but device"
			       " does not advertise support for FUA write\n",
			       cdb[0]);
			वापस -EINVAL;
		पूर्ण
		cmd->se_cmd_flags |= SCF_FUA;
	पूर्ण
	वापस 0;
पूर्ण

sense_reason_t
sbc_parse_cdb(काष्ठा se_cmd *cmd, काष्ठा sbc_ops *ops)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित अक्षर *cdb = cmd->t_task_cdb;
	अचिन्हित पूर्णांक size;
	u32 sectors = 0;
	sense_reason_t ret;

	cmd->protocol_data = ops;

	चयन (cdb[0]) अणु
	हाल READ_6:
		sectors = transport_get_sectors_6(cdb);
		cmd->t_task_lba = transport_lba_21(cdb);
		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_rw;
		अवरोध;
	हाल READ_10:
		sectors = transport_get_sectors_10(cdb);
		cmd->t_task_lba = transport_lba_32(cdb);

		अगर (sbc_check_dpofua(dev, cmd, cdb))
			वापस TCM_INVALID_CDB_FIELD;

		ret = sbc_check_prot(dev, cmd, cdb, sectors, false);
		अगर (ret)
			वापस ret;

		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_rw;
		अवरोध;
	हाल READ_12:
		sectors = transport_get_sectors_12(cdb);
		cmd->t_task_lba = transport_lba_32(cdb);

		अगर (sbc_check_dpofua(dev, cmd, cdb))
			वापस TCM_INVALID_CDB_FIELD;

		ret = sbc_check_prot(dev, cmd, cdb, sectors, false);
		अगर (ret)
			वापस ret;

		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_rw;
		अवरोध;
	हाल READ_16:
		sectors = transport_get_sectors_16(cdb);
		cmd->t_task_lba = transport_lba_64(cdb);

		अगर (sbc_check_dpofua(dev, cmd, cdb))
			वापस TCM_INVALID_CDB_FIELD;

		ret = sbc_check_prot(dev, cmd, cdb, sectors, false);
		अगर (ret)
			वापस ret;

		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_rw;
		अवरोध;
	हाल WRITE_6:
		sectors = transport_get_sectors_6(cdb);
		cmd->t_task_lba = transport_lba_21(cdb);
		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_rw;
		अवरोध;
	हाल WRITE_10:
	हाल WRITE_VERIFY:
		sectors = transport_get_sectors_10(cdb);
		cmd->t_task_lba = transport_lba_32(cdb);

		अगर (sbc_check_dpofua(dev, cmd, cdb))
			वापस TCM_INVALID_CDB_FIELD;

		ret = sbc_check_prot(dev, cmd, cdb, sectors, true);
		अगर (ret)
			वापस ret;

		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_rw;
		अवरोध;
	हाल WRITE_12:
		sectors = transport_get_sectors_12(cdb);
		cmd->t_task_lba = transport_lba_32(cdb);

		अगर (sbc_check_dpofua(dev, cmd, cdb))
			वापस TCM_INVALID_CDB_FIELD;

		ret = sbc_check_prot(dev, cmd, cdb, sectors, true);
		अगर (ret)
			वापस ret;

		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_rw;
		अवरोध;
	हाल WRITE_16:
	हाल WRITE_VERIFY_16:
		sectors = transport_get_sectors_16(cdb);
		cmd->t_task_lba = transport_lba_64(cdb);

		अगर (sbc_check_dpofua(dev, cmd, cdb))
			वापस TCM_INVALID_CDB_FIELD;

		ret = sbc_check_prot(dev, cmd, cdb, sectors, true);
		अगर (ret)
			वापस ret;

		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_rw;
		अवरोध;
	हाल XDWRITEREAD_10:
		अगर (cmd->data_direction != DMA_TO_DEVICE ||
		    !(cmd->se_cmd_flags & SCF_BIDI))
			वापस TCM_INVALID_CDB_FIELD;
		sectors = transport_get_sectors_10(cdb);

		अगर (sbc_check_dpofua(dev, cmd, cdb))
			वापस TCM_INVALID_CDB_FIELD;

		cmd->t_task_lba = transport_lba_32(cdb);
		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;

		/*
		 * Setup BIDI XOR callback to be run after I/O completion.
		 */
		cmd->execute_cmd = sbc_execute_rw;
		cmd->transport_complete_callback = &xdपढ़ोग_लिखो_callback;
		अवरोध;
	हाल VARIABLE_LENGTH_CMD:
	अणु
		u16 service_action = get_unaligned_be16(&cdb[8]);
		चयन (service_action) अणु
		हाल XDWRITEREAD_32:
			sectors = transport_get_sectors_32(cdb);

			अगर (sbc_check_dpofua(dev, cmd, cdb))
				वापस TCM_INVALID_CDB_FIELD;
			/*
			 * Use WRITE_32 and READ_32 opcodes क्रम the emulated
			 * XDWRITE_READ_32 logic.
			 */
			cmd->t_task_lba = transport_lba_64_ext(cdb);
			cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;

			/*
			 * Setup BIDI XOR callback to be run during after I/O
			 * completion.
			 */
			cmd->execute_cmd = sbc_execute_rw;
			cmd->transport_complete_callback = &xdपढ़ोग_लिखो_callback;
			अवरोध;
		हाल WRITE_SAME_32:
			sectors = transport_get_sectors_32(cdb);
			अगर (!sectors) अणु
				pr_err("WSNZ=1, WRITE_SAME w/sectors=0 not"
				       " supported\n");
				वापस TCM_INVALID_CDB_FIELD;
			पूर्ण

			size = sbc_get_size(cmd, 1);
			cmd->t_task_lba = get_unaligned_be64(&cdb[12]);

			ret = sbc_setup_ग_लिखो_same(cmd, &cdb[10], ops);
			अगर (ret)
				वापस ret;
			अवरोध;
		शेष:
			pr_err("VARIABLE_LENGTH_CMD service action"
				" 0x%04x not supported\n", service_action);
			वापस TCM_UNSUPPORTED_SCSI_OPCODE;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल COMPARE_AND_WRITE:
		अगर (!dev->dev_attrib.emulate_caw) अणु
			pr_err_ratelimited("se_device %s/%s (vpd_unit_serial %s) reject COMPARE_AND_WRITE\n",
					   dev->se_hba->backend->ops->name,
					   config_item_name(&dev->dev_group.cg_item),
					   dev->t10_wwn.unit_serial);
			वापस TCM_UNSUPPORTED_SCSI_OPCODE;
		पूर्ण
		sectors = cdb[13];
		/*
		 * Currently enक्रमce COMPARE_AND_WRITE क्रम a single sector
		 */
		अगर (sectors > 1) अणु
			pr_err("COMPARE_AND_WRITE contains NoLB: %u greater"
			       " than 1\n", sectors);
			वापस TCM_INVALID_CDB_FIELD;
		पूर्ण
		अगर (sbc_check_dpofua(dev, cmd, cdb))
			वापस TCM_INVALID_CDB_FIELD;

		/*
		 * Double size because we have two buffers, note that
		 * zero is not an error..
		 */
		size = 2 * sbc_get_size(cmd, sectors);
		cmd->t_task_lba = get_unaligned_be64(&cdb[2]);
		cmd->t_task_nolb = sectors;
		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB | SCF_COMPARE_AND_WRITE;
		cmd->execute_cmd = sbc_compare_and_ग_लिखो;
		cmd->transport_complete_callback = compare_and_ग_लिखो_callback;
		अवरोध;
	हाल READ_CAPACITY:
		size = READ_CAP_LEN;
		cmd->execute_cmd = sbc_emulate_पढ़ोcapacity;
		अवरोध;
	हाल SERVICE_ACTION_IN_16:
		चयन (cmd->t_task_cdb[1] & 0x1f) अणु
		हाल SAI_READ_CAPACITY_16:
			cmd->execute_cmd = sbc_emulate_पढ़ोcapacity_16;
			अवरोध;
		हाल SAI_REPORT_REFERRALS:
			cmd->execute_cmd = target_emulate_report_referrals;
			अवरोध;
		शेष:
			pr_err("Unsupported SA: 0x%02x\n",
				cmd->t_task_cdb[1] & 0x1f);
			वापस TCM_INVALID_CDB_FIELD;
		पूर्ण
		size = get_unaligned_be32(&cdb[10]);
		अवरोध;
	हाल SYNCHRONIZE_CACHE:
	हाल SYNCHRONIZE_CACHE_16:
		अगर (cdb[0] == SYNCHRONIZE_CACHE) अणु
			sectors = transport_get_sectors_10(cdb);
			cmd->t_task_lba = transport_lba_32(cdb);
		पूर्ण अन्यथा अणु
			sectors = transport_get_sectors_16(cdb);
			cmd->t_task_lba = transport_lba_64(cdb);
		पूर्ण
		अगर (ops->execute_sync_cache) अणु
			cmd->execute_cmd = ops->execute_sync_cache;
			जाओ check_lba;
		पूर्ण
		size = 0;
		cmd->execute_cmd = sbc_emulate_noop;
		अवरोध;
	हाल UNMAP:
		अगर (!ops->execute_unmap)
			वापस TCM_UNSUPPORTED_SCSI_OPCODE;

		अगर (!dev->dev_attrib.emulate_tpu) अणु
			pr_err("Got UNMAP, but backend device has"
			       " emulate_tpu disabled\n");
			वापस TCM_UNSUPPORTED_SCSI_OPCODE;
		पूर्ण
		size = get_unaligned_be16(&cdb[7]);
		cmd->execute_cmd = sbc_execute_unmap;
		अवरोध;
	हाल WRITE_SAME_16:
		sectors = transport_get_sectors_16(cdb);
		अगर (!sectors) अणु
			pr_err("WSNZ=1, WRITE_SAME w/sectors=0 not supported\n");
			वापस TCM_INVALID_CDB_FIELD;
		पूर्ण

		size = sbc_get_size(cmd, 1);
		cmd->t_task_lba = get_unaligned_be64(&cdb[2]);

		ret = sbc_setup_ग_लिखो_same(cmd, &cdb[1], ops);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल WRITE_SAME:
		sectors = transport_get_sectors_10(cdb);
		अगर (!sectors) अणु
			pr_err("WSNZ=1, WRITE_SAME w/sectors=0 not supported\n");
			वापस TCM_INVALID_CDB_FIELD;
		पूर्ण

		size = sbc_get_size(cmd, 1);
		cmd->t_task_lba = get_unaligned_be32(&cdb[2]);

		/*
		 * Follow sbcr26 with WRITE_SAME (10) and check क्रम the existence
		 * of byte 1 bit 3 UNMAP instead of original reserved field
		 */
		ret = sbc_setup_ग_लिखो_same(cmd, &cdb[1], ops);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल VERIFY:
	हाल VERIFY_16:
		size = 0;
		अगर (cdb[0] == VERIFY) अणु
			sectors = transport_get_sectors_10(cdb);
			cmd->t_task_lba = transport_lba_32(cdb);
		पूर्ण अन्यथा अणु
			sectors = transport_get_sectors_16(cdb);
			cmd->t_task_lba = transport_lba_64(cdb);
		पूर्ण
		cmd->execute_cmd = sbc_emulate_noop;
		जाओ check_lba;
	हाल REZERO_UNIT:
	हाल SEEK_6:
	हाल SEEK_10:
		/*
		 * There are still clients out there which use these old SCSI-2
		 * commands. This मुख्यly happens when running VMs with legacy
		 * guest प्रणालीs, connected via SCSI command pass-through to
		 * iSCSI tarमाला_लो. Make them happy and वापस status GOOD.
		 */
		size = 0;
		cmd->execute_cmd = sbc_emulate_noop;
		अवरोध;
	हाल START_STOP:
		size = 0;
		cmd->execute_cmd = sbc_emulate_startstop;
		अवरोध;
	शेष:
		ret = spc_parse_cdb(cmd, &size);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* reject any command that we करोn't have a handler क्रम */
	अगर (!cmd->execute_cmd)
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;

	अगर (cmd->se_cmd_flags & SCF_SCSI_DATA_CDB) अणु
		अचिन्हित दीर्घ दीर्घ end_lba;
check_lba:
		end_lba = dev->transport->get_blocks(dev) + 1;
		अगर (((cmd->t_task_lba + sectors) < cmd->t_task_lba) ||
		    ((cmd->t_task_lba + sectors) > end_lba)) अणु
			pr_err("cmd exceeds last lba %llu "
				"(lba %llu, sectors %u)\n",
				end_lba, cmd->t_task_lba, sectors);
			वापस TCM_ADDRESS_OUT_OF_RANGE;
		पूर्ण

		अगर (!(cmd->se_cmd_flags & SCF_COMPARE_AND_WRITE))
			size = sbc_get_size(cmd, sectors);
	पूर्ण

	वापस target_cmd_size_check(cmd, size);
पूर्ण
EXPORT_SYMBOL(sbc_parse_cdb);

u32 sbc_get_device_type(काष्ठा se_device *dev)
अणु
	वापस TYPE_DISK;
पूर्ण
EXPORT_SYMBOL(sbc_get_device_type);

अटल sense_reason_t
sbc_execute_unmap(काष्ठा se_cmd *cmd)
अणु
	काष्ठा sbc_ops *ops = cmd->protocol_data;
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित अक्षर *buf, *ptr = शून्य;
	sector_t lba;
	पूर्णांक size;
	u32 range;
	sense_reason_t ret = 0;
	पूर्णांक dl, bd_dl;

	/* We never set ANC_SUP */
	अगर (cmd->t_task_cdb[1])
		वापस TCM_INVALID_CDB_FIELD;

	अगर (cmd->data_length == 0) अणु
		target_complete_cmd(cmd, SAM_STAT_GOOD);
		वापस 0;
	पूर्ण

	अगर (cmd->data_length < 8) अणु
		pr_warn("UNMAP parameter list length %u too small\n",
			cmd->data_length);
		वापस TCM_PARAMETER_LIST_LENGTH_ERROR;
	पूर्ण

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	dl = get_unaligned_be16(&buf[0]);
	bd_dl = get_unaligned_be16(&buf[2]);

	size = cmd->data_length - 8;
	अगर (bd_dl > size)
		pr_warn("UNMAP parameter list length %u too small, ignoring bd_dl %u\n",
			cmd->data_length, bd_dl);
	अन्यथा
		size = bd_dl;

	अगर (size / 16 > dev->dev_attrib.max_unmap_block_desc_count) अणु
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ err;
	पूर्ण

	/* First UNMAP block descriptor starts at 8 byte offset */
	ptr = &buf[8];
	pr_debug("UNMAP: Sub: %s Using dl: %u bd_dl: %u size: %u"
		" ptr: %p\n", dev->transport->name, dl, bd_dl, size, ptr);

	जबतक (size >= 16) अणु
		lba = get_unaligned_be64(&ptr[0]);
		range = get_unaligned_be32(&ptr[8]);
		pr_debug("UNMAP: Using lba: %llu and range: %u\n",
				 (अचिन्हित दीर्घ दीर्घ)lba, range);

		अगर (range > dev->dev_attrib.max_unmap_lba_count) अणु
			ret = TCM_INVALID_PARAMETER_LIST;
			जाओ err;
		पूर्ण

		अगर (lba + range > dev->transport->get_blocks(dev) + 1) अणु
			ret = TCM_ADDRESS_OUT_OF_RANGE;
			जाओ err;
		पूर्ण

		अगर (range) अणु
			ret = ops->execute_unmap(cmd, lba, range);
			अगर (ret)
				जाओ err;
		पूर्ण

		ptr += 16;
		size -= 16;
	पूर्ण

err:
	transport_kunmap_data_sg(cmd);
	अगर (!ret)
		target_complete_cmd(cmd, GOOD);
	वापस ret;
पूर्ण

व्योम
sbc_dअगर_generate(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा t10_pi_tuple *sdt;
	काष्ठा scatterlist *dsg = cmd->t_data_sg, *psg;
	sector_t sector = cmd->t_task_lba;
	व्योम *daddr, *paddr;
	पूर्णांक i, j, offset = 0;
	अचिन्हित पूर्णांक block_size = dev->dev_attrib.block_size;

	क्रम_each_sg(cmd->t_prot_sg, psg, cmd->t_prot_nents, i) अणु
		paddr = kmap_atomic(sg_page(psg)) + psg->offset;
		daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;

		क्रम (j = 0; j < psg->length;
				j += माप(*sdt)) अणु
			__u16 crc;
			अचिन्हित पूर्णांक avail;

			अगर (offset >= dsg->length) अणु
				offset -= dsg->length;
				kunmap_atomic(daddr - dsg->offset);
				dsg = sg_next(dsg);
				अगर (!dsg) अणु
					kunmap_atomic(paddr - psg->offset);
					वापस;
				पूर्ण
				daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;
			पूर्ण

			sdt = paddr + j;
			avail = min(block_size, dsg->length - offset);
			crc = crc_t10dअगर(daddr + offset, avail);
			अगर (avail < block_size) अणु
				kunmap_atomic(daddr - dsg->offset);
				dsg = sg_next(dsg);
				अगर (!dsg) अणु
					kunmap_atomic(paddr - psg->offset);
					वापस;
				पूर्ण
				daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;
				offset = block_size - avail;
				crc = crc_t10dअगर_update(crc, daddr, offset);
			पूर्ण अन्यथा अणु
				offset += block_size;
			पूर्ण

			sdt->guard_tag = cpu_to_be16(crc);
			अगर (cmd->prot_type == TARGET_DIF_TYPE1_PROT)
				sdt->ref_tag = cpu_to_be32(sector & 0xffffffff);
			sdt->app_tag = 0;

			pr_debug("DIF %s INSERT sector: %llu guard_tag: 0x%04x"
				 " app_tag: 0x%04x ref_tag: %u\n",
				 (cmd->data_direction == DMA_TO_DEVICE) ?
				 "WRITE" : "READ", (अचिन्हित दीर्घ दीर्घ)sector,
				 sdt->guard_tag, sdt->app_tag,
				 be32_to_cpu(sdt->ref_tag));

			sector++;
		पूर्ण

		kunmap_atomic(daddr - dsg->offset);
		kunmap_atomic(paddr - psg->offset);
	पूर्ण
पूर्ण

अटल sense_reason_t
sbc_dअगर_v1_verअगरy(काष्ठा se_cmd *cmd, काष्ठा t10_pi_tuple *sdt,
		  __u16 crc, sector_t sector, अचिन्हित पूर्णांक ei_lba)
अणु
	__be16 csum;

	अगर (!(cmd->prot_checks & TARGET_DIF_CHECK_GUARD))
		जाओ check_ref;

	csum = cpu_to_be16(crc);

	अगर (sdt->guard_tag != csum) अणु
		pr_err("DIFv1 checksum failed on sector %llu guard tag 0x%04x"
			" csum 0x%04x\n", (अचिन्हित दीर्घ दीर्घ)sector,
			be16_to_cpu(sdt->guard_tag), be16_to_cpu(csum));
		वापस TCM_LOGICAL_BLOCK_GUARD_CHECK_FAILED;
	पूर्ण

check_ref:
	अगर (!(cmd->prot_checks & TARGET_DIF_CHECK_REFTAG))
		वापस 0;

	अगर (cmd->prot_type == TARGET_DIF_TYPE1_PROT &&
	    be32_to_cpu(sdt->ref_tag) != (sector & 0xffffffff)) अणु
		pr_err("DIFv1 Type 1 reference failed on sector: %llu tag: 0x%08x"
		       " sector MSB: 0x%08x\n", (अचिन्हित दीर्घ दीर्घ)sector,
		       be32_to_cpu(sdt->ref_tag), (u32)(sector & 0xffffffff));
		वापस TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED;
	पूर्ण

	अगर (cmd->prot_type == TARGET_DIF_TYPE2_PROT &&
	    be32_to_cpu(sdt->ref_tag) != ei_lba) अणु
		pr_err("DIFv1 Type 2 reference failed on sector: %llu tag: 0x%08x"
		       " ei_lba: 0x%08x\n", (अचिन्हित दीर्घ दीर्घ)sector,
			be32_to_cpu(sdt->ref_tag), ei_lba);
		वापस TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED;
	पूर्ण

	वापस 0;
पूर्ण

व्योम sbc_dअगर_copy_prot(काष्ठा se_cmd *cmd, अचिन्हित पूर्णांक sectors, bool पढ़ो,
		       काष्ठा scatterlist *sg, पूर्णांक sg_off)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा scatterlist *psg;
	व्योम *paddr, *addr;
	अचिन्हित पूर्णांक i, len, left;
	अचिन्हित पूर्णांक offset = sg_off;

	अगर (!sg)
		वापस;

	left = sectors * dev->prot_length;

	क्रम_each_sg(cmd->t_prot_sg, psg, cmd->t_prot_nents, i) अणु
		अचिन्हित पूर्णांक psg_len, copied = 0;

		paddr = kmap_atomic(sg_page(psg)) + psg->offset;
		psg_len = min(left, psg->length);
		जबतक (psg_len) अणु
			len = min(psg_len, sg->length - offset);
			addr = kmap_atomic(sg_page(sg)) + sg->offset + offset;

			अगर (पढ़ो)
				स_नकल(paddr + copied, addr, len);
			अन्यथा
				स_नकल(addr, paddr + copied, len);

			left -= len;
			offset += len;
			copied += len;
			psg_len -= len;

			kunmap_atomic(addr - sg->offset - offset);

			अगर (offset >= sg->length) अणु
				sg = sg_next(sg);
				offset = 0;
			पूर्ण
		पूर्ण
		kunmap_atomic(paddr - psg->offset);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sbc_dअगर_copy_prot);

sense_reason_t
sbc_dअगर_verअगरy(काष्ठा se_cmd *cmd, sector_t start, अचिन्हित पूर्णांक sectors,
	       अचिन्हित पूर्णांक ei_lba, काष्ठा scatterlist *psg, पूर्णांक psg_off)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा t10_pi_tuple *sdt;
	काष्ठा scatterlist *dsg = cmd->t_data_sg;
	sector_t sector = start;
	व्योम *daddr, *paddr;
	पूर्णांक i;
	sense_reason_t rc;
	पूर्णांक dsg_off = 0;
	अचिन्हित पूर्णांक block_size = dev->dev_attrib.block_size;

	क्रम (; psg && sector < start + sectors; psg = sg_next(psg)) अणु
		paddr = kmap_atomic(sg_page(psg)) + psg->offset;
		daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;

		क्रम (i = psg_off; i < psg->length &&
				sector < start + sectors;
				i += माप(*sdt)) अणु
			__u16 crc;
			अचिन्हित पूर्णांक avail;

			अगर (dsg_off >= dsg->length) अणु
				dsg_off -= dsg->length;
				kunmap_atomic(daddr - dsg->offset);
				dsg = sg_next(dsg);
				अगर (!dsg) अणु
					kunmap_atomic(paddr - psg->offset);
					वापस 0;
				पूर्ण
				daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;
			पूर्ण

			sdt = paddr + i;

			pr_debug("DIF READ sector: %llu guard_tag: 0x%04x"
				 " app_tag: 0x%04x ref_tag: %u\n",
				 (अचिन्हित दीर्घ दीर्घ)sector, sdt->guard_tag,
				 sdt->app_tag, be32_to_cpu(sdt->ref_tag));

			अगर (sdt->app_tag == T10_PI_APP_ESCAPE) अणु
				dsg_off += block_size;
				जाओ next;
			पूर्ण

			avail = min(block_size, dsg->length - dsg_off);
			crc = crc_t10dअगर(daddr + dsg_off, avail);
			अगर (avail < block_size) अणु
				kunmap_atomic(daddr - dsg->offset);
				dsg = sg_next(dsg);
				अगर (!dsg) अणु
					kunmap_atomic(paddr - psg->offset);
					वापस 0;
				पूर्ण
				daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;
				dsg_off = block_size - avail;
				crc = crc_t10dअगर_update(crc, daddr, dsg_off);
			पूर्ण अन्यथा अणु
				dsg_off += block_size;
			पूर्ण

			rc = sbc_dअगर_v1_verअगरy(cmd, sdt, crc, sector, ei_lba);
			अगर (rc) अणु
				kunmap_atomic(daddr - dsg->offset);
				kunmap_atomic(paddr - psg->offset);
				cmd->sense_info = sector;
				वापस rc;
			पूर्ण
next:
			sector++;
			ei_lba++;
		पूर्ण

		psg_off = 0;
		kunmap_atomic(daddr - dsg->offset);
		kunmap_atomic(paddr - psg->offset);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sbc_dअगर_verअगरy);
