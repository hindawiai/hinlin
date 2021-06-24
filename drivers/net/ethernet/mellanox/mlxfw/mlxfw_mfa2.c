<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2019 Mellanox Technologies. All rights reserved */

#घोषणा pr_fmt(fmt) "mlxfw_mfa2: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/xz.h>
#समावेश "mlxfw_mfa2.h"
#समावेश "mlxfw_mfa2_file.h"
#समावेश "mlxfw_mfa2_tlv.h"
#समावेश "mlxfw_mfa2_format.h"
#समावेश "mlxfw_mfa2_tlv_multi.h"

/*               MFA2 खाता
 *  +----------------------------------+
 *  |        MFA2 finger prपूर्णांक         |
 *  +----------------------------------+
 *  |   package descriptor multi_tlv   |
 *  | +------------------------------+ |     +-----------------+
 *  | |    package descriptor tlv    +-----> |num_devices=n    |
 *  | +------------------------------+ |     |num_components=m |
 *  +----------------------------------+     |CB offset        |
 *  |    device descriptor multi_tlv   |     |...              |
 *  | +------------------------------+ |     |                 |
 *  | |           PSID tlv           | |     +-----------------+
 *  | +------------------------------+ |
 *  | |     component index tlv      | |
 *  | +------------------------------+ |
 *  +----------------------------------+
 *  |  component descriptor multi_tlv  |
 *  | +------------------------------+ |     +-----------------+
 *  | |  component descriptor tlv    +-----> |Among others:    |
 *  | +------------------------------+ |     |CB offset=o      |
 *  +----------------------------------+     |comp index=i     |
 *  |                                  |     |...              |
 *  |                                  |     |                 |
 *  |                                  |     +-----------------+
 *  |        COMPONENT BLOCK (CB)      |
 *  |                                  |
 *  |                                  |
 *  |                                  |
 *  +----------------------------------+
 *
 * On the top level, an MFA2 file contains:
 *  - Fingerprपूर्णांक
 *  - Several multi_tlvs (TLVs of type MLXFW_MFA2_TLV_MULTI, as defined in
 *    mlxfw_mfa2_क्रमmat.h)
 *  - Compresses content block
 *
 * The first multi_tlv
 * -------------------
 * The first multi TLV is treated as package descriptor, and expected to have a
 * first TLV child of type MLXFW_MFA2_TLV_PACKAGE_DESCRIPTOR which contains all
 * the global inक्रमmation needed to parse the file. Among others, it contains
 * the number of device descriptors and component descriptor following this
 * multi TLV.
 *
 * The device descriptor multi_tlv
 * -------------------------------
 * The multi TLVs following the package descriptor are treated as device
 * descriptor, and are expected to have the following children:
 *  - PSID TLV child of type MLXFW_MFA2_TLV_PSID containing that device PSID.
 *  - Component index of type MLXFW_MFA2_TLV_COMPONENT_PTR that contains that
 *    device component index.
 *
 * The component descriptor multi_tlv
 * ----------------------------------
 * The multi TLVs following the device descriptor multi TLVs are treated as
 * component descriptor, and are expected to have a first child of type
 * MLXFW_MFA2_TLV_COMPONENT_DESCRIPTOR that contains mostly the component index,
 * needed क्रम the flash process and the offset to the binary within the
 * component block.
 */

अटल स्थिर u8 mlxfw_mfa2_fingerprपूर्णांक[] = "MLNX.MFA2.XZ.00!";
अटल स्थिर पूर्णांक mlxfw_mfa2_fingerprपूर्णांक_len =
			माप(mlxfw_mfa2_fingerprपूर्णांक) - 1;

अटल स्थिर u8 mlxfw_mfa2_comp_magic[] = "#BIN.COMPONENT!#";
अटल स्थिर पूर्णांक mlxfw_mfa2_comp_magic_len = माप(mlxfw_mfa2_comp_magic) - 1;

bool mlxfw_mfa2_check(स्थिर काष्ठा firmware *fw)
अणु
	अगर (fw->size < माप(mlxfw_mfa2_fingerprपूर्णांक))
		वापस false;

	वापस स_भेद(fw->data, mlxfw_mfa2_fingerprपूर्णांक,
		      mlxfw_mfa2_fingerprपूर्णांक_len) == 0;
पूर्ण

अटल bool
mlxfw_mfa2_tlv_multi_validate(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
			      स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv *tlv;
	u16 idx;

	/* Check that all children are valid */
	mlxfw_mfa2_tlv_multi_क्रमeach(mfa2_file, tlv, idx, multi) अणु
		अगर (!tlv) अणु
			pr_err("Multi has invalid child");
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल bool
mlxfw_mfa2_file_dev_validate(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
			     स्थिर काष्ठा mlxfw_mfa2_tlv *dev_tlv,
			     u16 dev_idx)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv_component_ptr *cptr;
	स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi;
	स्थिर काष्ठा mlxfw_mfa2_tlv_psid *psid;
	स्थिर काष्ठा mlxfw_mfa2_tlv *tlv;
	u16 cptr_count;
	u16 cptr_idx;
	पूर्णांक err;

	pr_debug("Device %d\n", dev_idx);

	multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, dev_tlv);
	अगर (!multi) अणु
		pr_err("Device %d is not a valid TLV error\n", dev_idx);
		वापस false;
	पूर्ण

	अगर (!mlxfw_mfa2_tlv_multi_validate(mfa2_file, multi))
		वापस false;

	/* Validate the device has PSID tlv */
	tlv = mlxfw_mfa2_tlv_multi_child_find(mfa2_file, multi,
					      MLXFW_MFA2_TLV_PSID, 0);
	अगर (!tlv) अणु
		pr_err("Device %d does not have PSID\n", dev_idx);
		वापस false;
	पूर्ण

	psid = mlxfw_mfa2_tlv_psid_get(mfa2_file, tlv);
	अगर (!psid) अणु
		pr_err("Device %d PSID TLV is not valid\n", dev_idx);
		वापस false;
	पूर्ण

	prपूर्णांक_hex_dump_debug("  -- Device PSID ", DUMP_PREFIX_NONE, 16, 16,
			     psid->psid, be16_to_cpu(tlv->len), true);

	/* Validate the device has COMPONENT_PTR */
	err = mlxfw_mfa2_tlv_multi_child_count(mfa2_file, multi,
					       MLXFW_MFA2_TLV_COMPONENT_PTR,
					       &cptr_count);
	अगर (err)
		वापस false;

	अगर (cptr_count == 0) अणु
		pr_err("Device %d has no components\n", dev_idx);
		वापस false;
	पूर्ण

	क्रम (cptr_idx = 0; cptr_idx < cptr_count; cptr_idx++) अणु
		tlv = mlxfw_mfa2_tlv_multi_child_find(mfa2_file, multi,
						      MLXFW_MFA2_TLV_COMPONENT_PTR,
						      cptr_idx);
		अगर (!tlv)
			वापस false;

		cptr = mlxfw_mfa2_tlv_component_ptr_get(mfa2_file, tlv);
		अगर (!cptr) अणु
			pr_err("Device %d COMPONENT_PTR TLV is not valid\n",
			       dev_idx);
			वापस false;
		पूर्ण

		pr_debug("  -- Component index %d\n",
			 be16_to_cpu(cptr->component_index));
	पूर्ण
	वापस true;
पूर्ण

अटल bool
mlxfw_mfa2_file_comp_validate(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
			      स्थिर काष्ठा mlxfw_mfa2_tlv *comp_tlv,
			      u16 comp_idx)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv_component_descriptor *cdesc;
	स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi;
	स्थिर काष्ठा mlxfw_mfa2_tlv *tlv;

	pr_debug("Component %d\n", comp_idx);

	multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, comp_tlv);
	अगर (!multi) अणु
		pr_err("Component %d is not a valid TLV error\n", comp_idx);
		वापस false;
	पूर्ण

	अगर (!mlxfw_mfa2_tlv_multi_validate(mfa2_file, multi))
		वापस false;

	/* Check that component have COMPONENT_DESCRIPTOR as first child */
	tlv = mlxfw_mfa2_tlv_multi_child(mfa2_file, multi);
	अगर (!tlv) अणु
		pr_err("Component descriptor %d multi TLV error\n", comp_idx);
		वापस false;
	पूर्ण

	cdesc = mlxfw_mfa2_tlv_component_descriptor_get(mfa2_file, tlv);
	अगर (!cdesc) अणु
		pr_err("Component %d does not have a valid descriptor\n",
		       comp_idx);
		वापस false;
	पूर्ण
	pr_debug("  -- Component type %d\n", be16_to_cpu(cdesc->identअगरier));
	pr_debug("  -- Offset 0x%llx and size %d\n",
		 ((u64) be32_to_cpu(cdesc->cb_offset_h) << 32)
		 | be32_to_cpu(cdesc->cb_offset_l), be32_to_cpu(cdesc->size));

	वापस true;
पूर्ण

अटल bool mlxfw_mfa2_file_validate(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv *tlv;
	u16 idx;

	pr_debug("Validating file\n");

	/* check that all the devices exist */
	mlxfw_mfa2_tlv_क्रमeach(mfa2_file, tlv, idx, mfa2_file->first_dev,
			       mfa2_file->dev_count) अणु
		अगर (!tlv) अणु
			pr_err("Device TLV error\n");
			वापस false;
		पूर्ण

		/* Check each device */
		अगर (!mlxfw_mfa2_file_dev_validate(mfa2_file, tlv, idx))
			वापस false;
	पूर्ण

	/* check that all the components exist */
	mlxfw_mfa2_tlv_क्रमeach(mfa2_file, tlv, idx, mfa2_file->first_component,
			       mfa2_file->component_count) अणु
		अगर (!tlv) अणु
			pr_err("Device TLV error\n");
			वापस false;
		पूर्ण

		/* Check each component */
		अगर (!mlxfw_mfa2_file_comp_validate(mfa2_file, tlv, idx))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

काष्ठा mlxfw_mfa2_file *mlxfw_mfa2_file_init(स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv_package_descriptor *pd;
	स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi;
	स्थिर काष्ठा mlxfw_mfa2_tlv *multi_child;
	स्थिर काष्ठा mlxfw_mfa2_tlv *first_tlv;
	काष्ठा mlxfw_mfa2_file *mfa2_file;
	स्थिर व्योम *first_tlv_ptr;
	स्थिर व्योम *cb_top_ptr;

	mfa2_file = kzalloc(माप(*mfa2_file), GFP_KERNEL);
	अगर (!mfa2_file)
		वापस ERR_PTR(-ENOMEM);

	mfa2_file->fw = fw;
	first_tlv_ptr = fw->data + NLA_ALIGN(mlxfw_mfa2_fingerprपूर्णांक_len);
	first_tlv = mlxfw_mfa2_tlv_get(mfa2_file, first_tlv_ptr);
	अगर (!first_tlv) अणु
		pr_err("Could not parse package descriptor TLV\n");
		जाओ err_out;
	पूर्ण

	multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, first_tlv);
	अगर (!multi) अणु
		pr_err("First TLV is not of valid multi type\n");
		जाओ err_out;
	पूर्ण

	multi_child = mlxfw_mfa2_tlv_multi_child(mfa2_file, multi);
	अगर (!multi_child)
		जाओ err_out;

	pd = mlxfw_mfa2_tlv_package_descriptor_get(mfa2_file, multi_child);
	अगर (!pd) अणु
		pr_err("Could not parse package descriptor TLV\n");
		जाओ err_out;
	पूर्ण

	mfa2_file->first_dev = mlxfw_mfa2_tlv_next(mfa2_file, first_tlv);
	अगर (!mfa2_file->first_dev) अणु
		pr_err("First device TLV is not valid\n");
		जाओ err_out;
	पूर्ण

	mfa2_file->dev_count = be16_to_cpu(pd->num_devices);
	mfa2_file->first_component = mlxfw_mfa2_tlv_advance(mfa2_file,
							    mfa2_file->first_dev,
							    mfa2_file->dev_count);
	mfa2_file->component_count = be16_to_cpu(pd->num_components);
	mfa2_file->cb = fw->data + NLA_ALIGN(be32_to_cpu(pd->cb_offset));
	अगर (!mlxfw_mfa2_valid_ptr(mfa2_file, mfa2_file->cb)) अणु
		pr_err("Component block is out side the file\n");
		जाओ err_out;
	पूर्ण
	mfa2_file->cb_archive_size = be32_to_cpu(pd->cb_archive_size);
	cb_top_ptr = mfa2_file->cb + mfa2_file->cb_archive_size - 1;
	अगर (!mlxfw_mfa2_valid_ptr(mfa2_file, cb_top_ptr)) अणु
		pr_err("Component block size is too big\n");
		जाओ err_out;
	पूर्ण

	अगर (!mlxfw_mfa2_file_validate(mfa2_file))
		जाओ err_out;
	वापस mfa2_file;
err_out:
	kमुक्त(mfa2_file);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल स्थिर काष्ठा mlxfw_mfa2_tlv_multi *
mlxfw_mfa2_tlv_dev_get(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
		       स्थिर अक्षर *psid, u16 psid_size)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv_psid *tlv_psid;
	स्थिर काष्ठा mlxfw_mfa2_tlv_multi *dev_multi;
	स्थिर काष्ठा mlxfw_mfa2_tlv *dev_tlv;
	स्थिर काष्ठा mlxfw_mfa2_tlv *tlv;
	u32 idx;

	/* क्रम each device tlv */
	mlxfw_mfa2_tlv_क्रमeach(mfa2_file, dev_tlv, idx, mfa2_file->first_dev,
			       mfa2_file->dev_count) अणु
		अगर (!dev_tlv)
			वापस शून्य;

		dev_multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, dev_tlv);
		अगर (!dev_multi)
			वापस शून्य;

		/* find psid child and compare */
		tlv = mlxfw_mfa2_tlv_multi_child_find(mfa2_file, dev_multi,
						      MLXFW_MFA2_TLV_PSID, 0);
		अगर (!tlv)
			वापस शून्य;
		अगर (be16_to_cpu(tlv->len) != psid_size)
			जारी;

		tlv_psid = mlxfw_mfa2_tlv_psid_get(mfa2_file, tlv);
		अगर (!tlv_psid)
			वापस शून्य;

		अगर (स_भेद(psid, tlv_psid->psid, psid_size) == 0)
			वापस dev_multi;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक mlxfw_mfa2_file_component_count(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
				    स्थिर अक्षर *psid, u32 psid_size,
				    u32 *p_count)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv_multi *dev_multi;
	u16 count;
	पूर्णांक err;

	dev_multi = mlxfw_mfa2_tlv_dev_get(mfa2_file, psid, psid_size);
	अगर (!dev_multi)
		वापस -EINVAL;

	err = mlxfw_mfa2_tlv_multi_child_count(mfa2_file, dev_multi,
					       MLXFW_MFA2_TLV_COMPONENT_PTR,
					       &count);
	अगर (err)
		वापस err;

	*p_count = count;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxfw_mfa2_xz_dec_run(काष्ठा xz_dec *xz_dec, काष्ठा xz_buf *xz_buf,
				 bool *finished)
अणु
	क्रमागत xz_ret xz_ret;

	xz_ret = xz_dec_run(xz_dec, xz_buf);

	चयन (xz_ret) अणु
	हाल XZ_STREAM_END:
		*finished = true;
		वापस 0;
	हाल XZ_OK:
		*finished = false;
		वापस 0;
	हाल XZ_MEM_ERROR:
		pr_err("xz no memory\n");
		वापस -ENOMEM;
	हाल XZ_DATA_ERROR:
		pr_err("xz file corrupted\n");
		वापस -EINVAL;
	हाल XZ_FORMAT_ERROR:
		pr_err("xz format not found\n");
		वापस -EINVAL;
	हाल XZ_OPTIONS_ERROR:
		pr_err("unsupported xz option\n");
		वापस -EINVAL;
	हाल XZ_MEMLIMIT_ERROR:
		pr_err("xz dictionary too small\n");
		वापस -EINVAL;
	शेष:
		pr_err("xz error %d\n", xz_ret);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxfw_mfa2_file_cb_offset_xz(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
					off_t off, माप_प्रकार size, u8 *buf)
अणु
	काष्ठा xz_dec *xz_dec;
	काष्ठा xz_buf dec_buf;
	off_t curr_off = 0;
	bool finished;
	पूर्णांक err;

	xz_dec = xz_dec_init(XZ_DYNALLOC, (u32) -1);
	अगर (!xz_dec)
		वापस -EINVAL;

	dec_buf.in_size = mfa2_file->cb_archive_size;
	dec_buf.in = mfa2_file->cb;
	dec_buf.in_pos = 0;
	dec_buf.out = buf;

	/* decode up to the offset */
	करो अणु
		dec_buf.out_pos = 0;
		dec_buf.out_size = min_t(माप_प्रकार, size, off - curr_off);
		अगर (dec_buf.out_size == 0)
			अवरोध;

		err = mlxfw_mfa2_xz_dec_run(xz_dec, &dec_buf, &finished);
		अगर (err)
			जाओ out;
		अगर (finished) अणु
			pr_err("xz section too short\n");
			err = -EINVAL;
			जाओ out;
		पूर्ण
		curr_off += dec_buf.out_pos;
	पूर्ण जबतक (curr_off != off);

	/* decode the needed section */
	dec_buf.out_pos = 0;
	dec_buf.out_size = size;
	err = mlxfw_mfa2_xz_dec_run(xz_dec, &dec_buf, &finished);
out:
	xz_dec_end(xz_dec);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा mlxfw_mfa2_tlv_component_descriptor *
mlxfw_mfa2_file_component_tlv_get(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
				  u16 comp_index)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv_multi *multi;
	स्थिर काष्ठा mlxfw_mfa2_tlv *multi_child;
	स्थिर काष्ठा mlxfw_mfa2_tlv *comp_tlv;

	अगर (comp_index > mfa2_file->component_count)
		वापस शून्य;

	comp_tlv = mlxfw_mfa2_tlv_advance(mfa2_file, mfa2_file->first_component,
					  comp_index);
	अगर (!comp_tlv)
		वापस शून्य;

	multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, comp_tlv);
	अगर (!multi)
		वापस शून्य;

	multi_child = mlxfw_mfa2_tlv_multi_child(mfa2_file, multi);
	अगर (!multi_child)
		वापस शून्य;

	वापस mlxfw_mfa2_tlv_component_descriptor_get(mfa2_file, multi_child);
पूर्ण

काष्ठा mlxfw_mfa2_comp_data अणु
	काष्ठा mlxfw_mfa2_component comp;
	u8 buff[];
पूर्ण;

अटल स्थिर काष्ठा mlxfw_mfa2_tlv_component_descriptor *
mlxfw_mfa2_file_component_find(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
			       स्थिर अक्षर *psid, पूर्णांक psid_size,
			       पूर्णांक component_index)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv_component_ptr *cptr;
	स्थिर काष्ठा mlxfw_mfa2_tlv_multi *dev_multi;
	स्थिर काष्ठा mlxfw_mfa2_tlv *cptr_tlv;
	u16 comp_idx;

	dev_multi = mlxfw_mfa2_tlv_dev_get(mfa2_file, psid, psid_size);
	अगर (!dev_multi)
		वापस शून्य;

	cptr_tlv = mlxfw_mfa2_tlv_multi_child_find(mfa2_file, dev_multi,
						   MLXFW_MFA2_TLV_COMPONENT_PTR,
						   component_index);
	अगर (!cptr_tlv)
		वापस शून्य;

	cptr = mlxfw_mfa2_tlv_component_ptr_get(mfa2_file, cptr_tlv);
	अगर (!cptr)
		वापस शून्य;

	comp_idx = be16_to_cpu(cptr->component_index);
	वापस mlxfw_mfa2_file_component_tlv_get(mfa2_file, comp_idx);
पूर्ण

काष्ठा mlxfw_mfa2_component *
mlxfw_mfa2_file_component_get(स्थिर काष्ठा mlxfw_mfa2_file *mfa2_file,
			      स्थिर अक्षर *psid, पूर्णांक psid_size,
			      पूर्णांक component_index)
अणु
	स्थिर काष्ठा mlxfw_mfa2_tlv_component_descriptor *comp;
	काष्ठा mlxfw_mfa2_comp_data *comp_data;
	u32 comp_buf_size;
	off_t cb_offset;
	u32 comp_size;
	पूर्णांक err;

	comp = mlxfw_mfa2_file_component_find(mfa2_file, psid, psid_size,
					      component_index);
	अगर (!comp)
		वापस ERR_PTR(-EINVAL);

	cb_offset = (u64) be32_to_cpu(comp->cb_offset_h) << 32 |
		    be32_to_cpu(comp->cb_offset_l);
	comp_size = be32_to_cpu(comp->size);
	comp_buf_size = comp_size + mlxfw_mfa2_comp_magic_len;

	comp_data = vzalloc(माप(*comp_data) + comp_buf_size);
	अगर (!comp_data)
		वापस ERR_PTR(-ENOMEM);
	comp_data->comp.data_size = comp_size;
	comp_data->comp.index = be16_to_cpu(comp->identअगरier);
	err = mlxfw_mfa2_file_cb_offset_xz(mfa2_file, cb_offset, comp_buf_size,
					   comp_data->buff);
	अगर (err) अणु
		pr_err("Component could not be reached in CB\n");
		जाओ err_out;
	पूर्ण

	अगर (स_भेद(comp_data->buff, mlxfw_mfa2_comp_magic,
		   mlxfw_mfa2_comp_magic_len) != 0) अणु
		pr_err("Component has wrong magic\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	comp_data->comp.data = comp_data->buff + mlxfw_mfa2_comp_magic_len;
	वापस &comp_data->comp;
err_out:
	vमुक्त(comp_data);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlxfw_mfa2_file_component_put(काष्ठा mlxfw_mfa2_component *comp)
अणु
	स्थिर काष्ठा mlxfw_mfa2_comp_data *comp_data;

	comp_data = container_of(comp, काष्ठा mlxfw_mfa2_comp_data, comp);
	vमुक्त(comp_data);
पूर्ण

व्योम mlxfw_mfa2_file_fini(काष्ठा mlxfw_mfa2_file *mfa2_file)
अणु
	kमुक्त(mfa2_file);
पूर्ण
