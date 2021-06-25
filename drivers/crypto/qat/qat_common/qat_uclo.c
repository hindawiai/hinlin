<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci_ids.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "icp_qat_uclo.h"
#समावेश "icp_qat_hal.h"
#समावेश "icp_qat_fw_loader_handle.h"

#घोषणा UWORD_CPYBUF_SIZE 1024
#घोषणा INVLD_UWORD 0xffffffffffull
#घोषणा PID_MINOR_REV 0xf
#घोषणा PID_MAJOR_REV (0xf << 4)

अटल पूर्णांक qat_uclo_init_ae_data(काष्ठा icp_qat_uclo_objhandle *obj_handle,
				 अचिन्हित पूर्णांक ae, अचिन्हित पूर्णांक image_num)
अणु
	काष्ठा icp_qat_uclo_aedata *ae_data;
	काष्ठा icp_qat_uclo_encapme *encap_image;
	काष्ठा icp_qat_uclo_page *page = शून्य;
	काष्ठा icp_qat_uclo_aeslice *ae_slice = शून्य;

	ae_data = &obj_handle->ae_data[ae];
	encap_image = &obj_handle->ae_uimage[image_num];
	ae_slice = &ae_data->ae_slices[ae_data->slice_num];
	ae_slice->encap_image = encap_image;

	अगर (encap_image->img_ptr) अणु
		ae_slice->ctx_mask_asचिन्हित =
					encap_image->img_ptr->ctx_asचिन्हित;
		ae_data->eff_ustore_size = obj_handle->ustore_phy_size;
	पूर्ण अन्यथा अणु
		ae_slice->ctx_mask_asचिन्हित = 0;
	पूर्ण
	ae_slice->region = kzalloc(माप(*ae_slice->region), GFP_KERNEL);
	अगर (!ae_slice->region)
		वापस -ENOMEM;
	ae_slice->page = kzalloc(माप(*ae_slice->page), GFP_KERNEL);
	अगर (!ae_slice->page)
		जाओ out_err;
	page = ae_slice->page;
	page->encap_page = encap_image->page;
	ae_slice->page->region = ae_slice->region;
	ae_data->slice_num++;
	वापस 0;
out_err:
	kमुक्त(ae_slice->region);
	ae_slice->region = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक qat_uclo_मुक्त_ae_data(काष्ठा icp_qat_uclo_aedata *ae_data)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!ae_data) अणु
		pr_err("QAT: bad argument, ae_data is NULL\n ");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ae_data->slice_num; i++) अणु
		kमुक्त(ae_data->ae_slices[i].region);
		ae_data->ae_slices[i].region = शून्य;
		kमुक्त(ae_data->ae_slices[i].page);
		ae_data->ae_slices[i].page = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल अक्षर *qat_uclo_get_string(काष्ठा icp_qat_uof_strtable *str_table,
				 अचिन्हित पूर्णांक str_offset)
अणु
	अगर (!str_table->table_len || str_offset > str_table->table_len)
		वापस शून्य;
	वापस (अक्षर *)(((uपूर्णांकptr_t)(str_table->strings)) + str_offset);
पूर्ण

अटल पूर्णांक qat_uclo_check_uof_क्रमmat(काष्ठा icp_qat_uof_filehdr *hdr)
अणु
	पूर्णांक maj = hdr->maj_ver & 0xff;
	पूर्णांक min = hdr->min_ver & 0xff;

	अगर (hdr->file_id != ICP_QAT_UOF_FID) अणु
		pr_err("QAT: Invalid header 0x%x\n", hdr->file_id);
		वापस -EINVAL;
	पूर्ण
	अगर (min != ICP_QAT_UOF_MINVER || maj != ICP_QAT_UOF_MAJVER) अणु
		pr_err("QAT: bad UOF version, major 0x%x, minor 0x%x\n",
		       maj, min);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_check_suof_क्रमmat(काष्ठा icp_qat_suof_filehdr *suof_hdr)
अणु
	पूर्णांक maj = suof_hdr->maj_ver & 0xff;
	पूर्णांक min = suof_hdr->min_ver & 0xff;

	अगर (suof_hdr->file_id != ICP_QAT_SUOF_FID) अणु
		pr_err("QAT: invalid header 0x%x\n", suof_hdr->file_id);
		वापस -EINVAL;
	पूर्ण
	अगर (suof_hdr->fw_type != 0) अणु
		pr_err("QAT: unsupported firmware type\n");
		वापस -EINVAL;
	पूर्ण
	अगर (suof_hdr->num_chunks <= 0x1) अणु
		pr_err("QAT: SUOF chunk amount is incorrect\n");
		वापस -EINVAL;
	पूर्ण
	अगर (maj != ICP_QAT_SUOF_MAJVER || min != ICP_QAT_SUOF_MINVER) अणु
		pr_err("QAT: bad SUOF version, major 0x%x, minor 0x%x\n",
		       maj, min);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qat_uclo_wr_sram_by_words(काष्ठा icp_qat_fw_loader_handle *handle,
				      अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक *val,
				      अचिन्हित पूर्णांक num_in_bytes)
अणु
	अचिन्हित पूर्णांक outval;
	अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *)val;

	जबतक (num_in_bytes) अणु
		स_नकल(&outval, ptr, 4);
		SRAM_WRITE(handle, addr, outval);
		num_in_bytes -= 4;
		ptr += 4;
		addr += 4;
	पूर्ण
पूर्ण

अटल व्योम qat_uclo_wr_umem_by_words(काष्ठा icp_qat_fw_loader_handle *handle,
				      अचिन्हित अक्षर ae, अचिन्हित पूर्णांक addr,
				      अचिन्हित पूर्णांक *val,
				      अचिन्हित पूर्णांक num_in_bytes)
अणु
	अचिन्हित पूर्णांक outval;
	अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *)val;

	addr >>= 0x2; /* convert to uword address */

	जबतक (num_in_bytes) अणु
		स_नकल(&outval, ptr, 4);
		qat_hal_wr_umem(handle, ae, addr++, 1, &outval);
		num_in_bytes -= 4;
		ptr += 4;
	पूर्ण
पूर्ण

अटल व्योम qat_uclo_batch_wr_umem(काष्ठा icp_qat_fw_loader_handle *handle,
				   अचिन्हित अक्षर ae,
				   काष्ठा icp_qat_uof_batch_init
				   *umem_init_header)
अणु
	काष्ठा icp_qat_uof_batch_init *umem_init;

	अगर (!umem_init_header)
		वापस;
	umem_init = umem_init_header->next;
	जबतक (umem_init) अणु
		अचिन्हित पूर्णांक addr, *value, size;

		ae = umem_init->ae;
		addr = umem_init->addr;
		value = umem_init->value;
		size = umem_init->size;
		qat_uclo_wr_umem_by_words(handle, ae, addr, value, size);
		umem_init = umem_init->next;
	पूर्ण
पूर्ण

अटल व्योम
qat_uclo_cleanup_batch_init_list(काष्ठा icp_qat_fw_loader_handle *handle,
				 काष्ठा icp_qat_uof_batch_init **base)
अणु
	काष्ठा icp_qat_uof_batch_init *umem_init;

	umem_init = *base;
	जबतक (umem_init) अणु
		काष्ठा icp_qat_uof_batch_init *pre;

		pre = umem_init;
		umem_init = umem_init->next;
		kमुक्त(pre);
	पूर्ण
	*base = शून्य;
पूर्ण

अटल पूर्णांक qat_uclo_parse_num(अक्षर *str, अचिन्हित पूर्णांक *num)
अणु
	अक्षर buf[16] = अणु0पूर्ण;
	अचिन्हित दीर्घ ae = 0;
	पूर्णांक i;

	म_नकलन(buf, str, 15);
	क्रम (i = 0; i < 16; i++) अणु
		अगर (!है_अंक(buf[i])) अणु
			buf[i] = '\0';
			अवरोध;
		पूर्ण
	पूर्ण
	अगर ((kम_से_अदीर्घ(buf, 10, &ae)))
		वापस -EFAULT;

	*num = (अचिन्हित पूर्णांक)ae;
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_fetch_iniपंचांगem_ae(काष्ठा icp_qat_fw_loader_handle *handle,
				     काष्ठा icp_qat_uof_iniपंचांगem *init_mem,
				     अचिन्हित पूर्णांक size_range, अचिन्हित पूर्णांक *ae)
अणु
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अक्षर *str;

	अगर ((init_mem->addr + init_mem->num_in_bytes) > (size_range << 0x2)) अणु
		pr_err("QAT: initmem is out of range");
		वापस -EINVAL;
	पूर्ण
	अगर (init_mem->scope != ICP_QAT_UOF_LOCAL_SCOPE) अणु
		pr_err("QAT: Memory scope for init_mem error\n");
		वापस -EINVAL;
	पूर्ण
	str = qat_uclo_get_string(&obj_handle->str_table, init_mem->sym_name);
	अगर (!str) अणु
		pr_err("QAT: AE name assigned in UOF init table is NULL\n");
		वापस -EINVAL;
	पूर्ण
	अगर (qat_uclo_parse_num(str, ae)) अणु
		pr_err("QAT: Parse num for AE number failed\n");
		वापस -EINVAL;
	पूर्ण
	अगर (*ae >= ICP_QAT_UCLO_MAX_AE) अणु
		pr_err("QAT: ae %d out of range\n", *ae);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_create_batch_init_list(काष्ठा icp_qat_fw_loader_handle
					   *handle, काष्ठा icp_qat_uof_iniपंचांगem
					   *init_mem, अचिन्हित पूर्णांक ae,
					   काष्ठा icp_qat_uof_batch_init
					   **init_tab_base)
अणु
	काष्ठा icp_qat_uof_batch_init *init_header, *tail;
	काष्ठा icp_qat_uof_batch_init *mem_init, *tail_old;
	काष्ठा icp_qat_uof_memvar_attr *mem_val_attr;
	अचिन्हित पूर्णांक i, flag = 0;

	mem_val_attr =
		(काष्ठा icp_qat_uof_memvar_attr *)((uपूर्णांकptr_t)init_mem +
		माप(काष्ठा icp_qat_uof_iniपंचांगem));

	init_header = *init_tab_base;
	अगर (!init_header) अणु
		init_header = kzalloc(माप(*init_header), GFP_KERNEL);
		अगर (!init_header)
			वापस -ENOMEM;
		init_header->size = 1;
		*init_tab_base = init_header;
		flag = 1;
	पूर्ण
	tail_old = init_header;
	जबतक (tail_old->next)
		tail_old = tail_old->next;
	tail = tail_old;
	क्रम (i = 0; i < init_mem->val_attr_num; i++) अणु
		mem_init = kzalloc(माप(*mem_init), GFP_KERNEL);
		अगर (!mem_init)
			जाओ out_err;
		mem_init->ae = ae;
		mem_init->addr = init_mem->addr + mem_val_attr->offset_in_byte;
		mem_init->value = &mem_val_attr->value;
		mem_init->size = 4;
		mem_init->next = शून्य;
		tail->next = mem_init;
		tail = mem_init;
		init_header->size += qat_hal_get_ins_num();
		mem_val_attr++;
	पूर्ण
	वापस 0;
out_err:
	/* Do not मुक्त the list head unless we allocated it. */
	tail_old = tail_old->next;
	अगर (flag) अणु
		kमुक्त(*init_tab_base);
		*init_tab_base = शून्य;
	पूर्ण

	जबतक (tail_old) अणु
		mem_init = tail_old->next;
		kमुक्त(tail_old);
		tail_old = mem_init;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक qat_uclo_init_lmem_seg(काष्ठा icp_qat_fw_loader_handle *handle,
				  काष्ठा icp_qat_uof_iniपंचांगem *init_mem)
अणु
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित पूर्णांक ae;

	अगर (qat_uclo_fetch_iniपंचांगem_ae(handle, init_mem,
				      handle->chip_info->lm_size, &ae))
		वापस -EINVAL;
	अगर (qat_uclo_create_batch_init_list(handle, init_mem, ae,
					    &obj_handle->lm_init_tab[ae]))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_init_umem_seg(काष्ठा icp_qat_fw_loader_handle *handle,
				  काष्ठा icp_qat_uof_iniपंचांगem *init_mem)
अणु
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित पूर्णांक ae, ustore_size, uaddr, i;
	काष्ठा icp_qat_uclo_aedata *aed;

	ustore_size = obj_handle->ustore_phy_size;
	अगर (qat_uclo_fetch_iniपंचांगem_ae(handle, init_mem, ustore_size, &ae))
		वापस -EINVAL;
	अगर (qat_uclo_create_batch_init_list(handle, init_mem, ae,
					    &obj_handle->umem_init_tab[ae]))
		वापस -EINVAL;
	/* set the highest ustore address referenced */
	uaddr = (init_mem->addr + init_mem->num_in_bytes) >> 0x2;
	aed = &obj_handle->ae_data[ae];
	क्रम (i = 0; i < aed->slice_num; i++) अणु
		अगर (aed->ae_slices[i].encap_image->uwords_num < uaddr)
			aed->ae_slices[i].encap_image->uwords_num = uaddr;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा ICP_DH895XCC_PESRAM_BAR_SIZE 0x80000
अटल पूर्णांक qat_uclo_init_ae_memory(काष्ठा icp_qat_fw_loader_handle *handle,
				   काष्ठा icp_qat_uof_iniपंचांगem *init_mem)
अणु
	चयन (init_mem->region) अणु
	हाल ICP_QAT_UOF_LMEM_REGION:
		अगर (qat_uclo_init_lmem_seg(handle, init_mem))
			वापस -EINVAL;
		अवरोध;
	हाल ICP_QAT_UOF_UMEM_REGION:
		अगर (qat_uclo_init_umem_seg(handle, init_mem))
			वापस -EINVAL;
		अवरोध;
	शेष:
		pr_err("QAT: initmem region error. region type=0x%x\n",
		       init_mem->region);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_init_ustore(काष्ठा icp_qat_fw_loader_handle *handle,
				काष्ठा icp_qat_uclo_encapme *image)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा icp_qat_uclo_encap_page *page;
	काष्ठा icp_qat_uof_image *uof_image;
	अचिन्हित अक्षर ae;
	अचिन्हित पूर्णांक ustore_size;
	अचिन्हित पूर्णांक patt_pos;
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित दीर्घ cfg_ae_mask = handle->cfg_ae_mask;
	u64 *fill_data;

	uof_image = image->img_ptr;
	fill_data = kसुस्मृति(ICP_QAT_UCLO_MAX_USTORE, माप(u64),
			    GFP_KERNEL);
	अगर (!fill_data)
		वापस -ENOMEM;
	क्रम (i = 0; i < ICP_QAT_UCLO_MAX_USTORE; i++)
		स_नकल(&fill_data[i], &uof_image->fill_pattern,
		       माप(u64));
	page = image->page;

	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		अगर (!test_bit(ae, (अचिन्हित दीर्घ *)&uof_image->ae_asचिन्हित))
			जारी;

		अगर (!test_bit(ae, &cfg_ae_mask))
			जारी;

		ustore_size = obj_handle->ae_data[ae].eff_ustore_size;
		patt_pos = page->beg_addr_p + page->micro_words_num;

		qat_hal_wr_uwords(handle, (अचिन्हित अक्षर)ae, 0,
				  page->beg_addr_p, &fill_data[0]);
		qat_hal_wr_uwords(handle, (अचिन्हित अक्षर)ae, patt_pos,
				  ustore_size - patt_pos + 1,
				  &fill_data[page->beg_addr_p]);
	पूर्ण
	kमुक्त(fill_data);
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_init_memory(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	पूर्णांक i, ae;
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	काष्ठा icp_qat_uof_iniपंचांगem *iniपंचांगem = obj_handle->init_mem_tab.init_mem;
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;

	क्रम (i = 0; i < obj_handle->init_mem_tab.entry_num; i++) अणु
		अगर (iniपंचांगem->num_in_bytes) अणु
			अगर (qat_uclo_init_ae_memory(handle, iniपंचांगem))
				वापस -EINVAL;
		पूर्ण
		iniपंचांगem = (काष्ठा icp_qat_uof_iniपंचांगem *)((uपूर्णांकptr_t)(
			(uपूर्णांकptr_t)iniपंचांगem +
			माप(काष्ठा icp_qat_uof_iniपंचांगem)) +
			(माप(काष्ठा icp_qat_uof_memvar_attr) *
			iniपंचांगem->val_attr_num));
	पूर्ण

	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		अगर (qat_hal_batch_wr_lm(handle, ae,
					obj_handle->lm_init_tab[ae])) अणु
			pr_err("QAT: fail to batch init lmem for AE %d\n", ae);
			वापस -EINVAL;
		पूर्ण
		qat_uclo_cleanup_batch_init_list(handle,
						 &obj_handle->lm_init_tab[ae]);
		qat_uclo_batch_wr_umem(handle, ae,
				       obj_handle->umem_init_tab[ae]);
		qat_uclo_cleanup_batch_init_list(handle,
						 &obj_handle->
						 umem_init_tab[ae]);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम *qat_uclo_find_chunk(काष्ठा icp_qat_uof_objhdr *obj_hdr,
				 अक्षर *chunk_id, व्योम *cur)
अणु
	पूर्णांक i;
	काष्ठा icp_qat_uof_chunkhdr *chunk_hdr =
	    (काष्ठा icp_qat_uof_chunkhdr *)
	    ((uपूर्णांकptr_t)obj_hdr + माप(काष्ठा icp_qat_uof_objhdr));

	क्रम (i = 0; i < obj_hdr->num_chunks; i++) अणु
		अगर ((cur < (व्योम *)&chunk_hdr[i]) &&
		    !म_भेदन(chunk_hdr[i].chunk_id, chunk_id,
			     ICP_QAT_UOF_OBJID_LEN)) अणु
			वापस &chunk_hdr[i];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक qat_uclo_calc_checksum(अचिन्हित पूर्णांक reg, पूर्णांक ch)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक topbit = 1 << 0xF;
	अचिन्हित पूर्णांक inbyte = (अचिन्हित पूर्णांक)((reg >> 0x18) ^ ch);

	reg ^= inbyte << 0x8;
	क्रम (i = 0; i < 0x8; i++) अणु
		अगर (reg & topbit)
			reg = (reg << 1) ^ 0x1021;
		अन्यथा
			reg <<= 1;
	पूर्ण
	वापस reg & 0xFFFF;
पूर्ण

अटल अचिन्हित पूर्णांक qat_uclo_calc_str_checksum(अक्षर *ptr, पूर्णांक num)
अणु
	अचिन्हित पूर्णांक chksum = 0;

	अगर (ptr)
		जबतक (num--)
			chksum = qat_uclo_calc_checksum(chksum, *ptr++);
	वापस chksum;
पूर्ण

अटल काष्ठा icp_qat_uclo_objhdr *
qat_uclo_map_chunk(अक्षर *buf, काष्ठा icp_qat_uof_filehdr *file_hdr,
		   अक्षर *chunk_id)
अणु
	काष्ठा icp_qat_uof_filechunkhdr *file_chunk;
	काष्ठा icp_qat_uclo_objhdr *obj_hdr;
	अक्षर *chunk;
	पूर्णांक i;

	file_chunk = (काष्ठा icp_qat_uof_filechunkhdr *)
		(buf + माप(काष्ठा icp_qat_uof_filehdr));
	क्रम (i = 0; i < file_hdr->num_chunks; i++) अणु
		अगर (!म_भेदन(file_chunk->chunk_id, chunk_id,
			     ICP_QAT_UOF_OBJID_LEN)) अणु
			chunk = buf + file_chunk->offset;
			अगर (file_chunk->checksum != qat_uclo_calc_str_checksum(
				chunk, file_chunk->size))
				अवरोध;
			obj_hdr = kzalloc(माप(*obj_hdr), GFP_KERNEL);
			अगर (!obj_hdr)
				अवरोध;
			obj_hdr->file_buff = chunk;
			obj_hdr->checksum = file_chunk->checksum;
			obj_hdr->size = file_chunk->size;
			वापस obj_hdr;
		पूर्ण
		file_chunk++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक
qat_uclo_check_image_compat(काष्ठा icp_qat_uof_encap_obj *encap_uof_obj,
			    काष्ठा icp_qat_uof_image *image)
अणु
	काष्ठा icp_qat_uof_objtable *uc_var_tab, *imp_var_tab, *imp_expr_tab;
	काष्ठा icp_qat_uof_objtable *neigh_reg_tab;
	काष्ठा icp_qat_uof_code_page *code_page;

	code_page = (काष्ठा icp_qat_uof_code_page *)
			((अक्षर *)image + माप(काष्ठा icp_qat_uof_image));
	uc_var_tab = (काष्ठा icp_qat_uof_objtable *)(encap_uof_obj->beg_uof +
		     code_page->uc_var_tab_offset);
	imp_var_tab = (काष्ठा icp_qat_uof_objtable *)(encap_uof_obj->beg_uof +
		      code_page->imp_var_tab_offset);
	imp_expr_tab = (काष्ठा icp_qat_uof_objtable *)
		       (encap_uof_obj->beg_uof +
		       code_page->imp_expr_tab_offset);
	अगर (uc_var_tab->entry_num || imp_var_tab->entry_num ||
	    imp_expr_tab->entry_num) अणु
		pr_err("QAT: UOF can't contain imported variable to be parsed\n");
		वापस -EINVAL;
	पूर्ण
	neigh_reg_tab = (काष्ठा icp_qat_uof_objtable *)
			(encap_uof_obj->beg_uof +
			code_page->neigh_reg_tab_offset);
	अगर (neigh_reg_tab->entry_num) अणु
		pr_err("QAT: UOF can't contain neighbor register table\n");
		वापस -EINVAL;
	पूर्ण
	अगर (image->numpages > 1) अणु
		pr_err("QAT: UOF can't contain multiple pages\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ICP_QAT_SHARED_USTORE_MODE(image->ae_mode)) अणु
		pr_err("QAT: UOF can't use shared control store feature\n");
		वापस -EFAULT;
	पूर्ण
	अगर (RELOADABLE_CTX_SHARED_MODE(image->ae_mode)) अणु
		pr_err("QAT: UOF can't use reloadable feature\n");
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qat_uclo_map_image_page(काष्ठा icp_qat_uof_encap_obj
				     *encap_uof_obj,
				     काष्ठा icp_qat_uof_image *img,
				     काष्ठा icp_qat_uclo_encap_page *page)
अणु
	काष्ठा icp_qat_uof_code_page *code_page;
	काष्ठा icp_qat_uof_code_area *code_area;
	काष्ठा icp_qat_uof_objtable *uword_block_tab;
	काष्ठा icp_qat_uof_uword_block *uwblock;
	पूर्णांक i;

	code_page = (काष्ठा icp_qat_uof_code_page *)
			((अक्षर *)img + माप(काष्ठा icp_qat_uof_image));
	page->def_page = code_page->def_page;
	page->page_region = code_page->page_region;
	page->beg_addr_v = code_page->beg_addr_v;
	page->beg_addr_p = code_page->beg_addr_p;
	code_area = (काष्ठा icp_qat_uof_code_area *)(encap_uof_obj->beg_uof +
						code_page->code_area_offset);
	page->micro_words_num = code_area->micro_words_num;
	uword_block_tab = (काष्ठा icp_qat_uof_objtable *)
			  (encap_uof_obj->beg_uof +
			  code_area->uword_block_tab);
	page->uwblock_num = uword_block_tab->entry_num;
	uwblock = (काष्ठा icp_qat_uof_uword_block *)((अक्षर *)uword_block_tab +
			माप(काष्ठा icp_qat_uof_objtable));
	page->uwblock = (काष्ठा icp_qat_uclo_encap_uwblock *)uwblock;
	क्रम (i = 0; i < uword_block_tab->entry_num; i++)
		page->uwblock[i].micro_words =
		(uपूर्णांकptr_t)encap_uof_obj->beg_uof + uwblock[i].uword_offset;
पूर्ण

अटल पूर्णांक qat_uclo_map_uimage(काष्ठा icp_qat_uclo_objhandle *obj_handle,
			       काष्ठा icp_qat_uclo_encapme *ae_uimage,
			       पूर्णांक max_image)
अणु
	पूर्णांक i, j;
	काष्ठा icp_qat_uof_chunkhdr *chunk_hdr = शून्य;
	काष्ठा icp_qat_uof_image *image;
	काष्ठा icp_qat_uof_objtable *ae_regtab;
	काष्ठा icp_qat_uof_objtable *init_reg_sym_tab;
	काष्ठा icp_qat_uof_objtable *sअवरोध_tab;
	काष्ठा icp_qat_uof_encap_obj *encap_uof_obj =
					&obj_handle->encap_uof_obj;

	क्रम (j = 0; j < max_image; j++) अणु
		chunk_hdr = qat_uclo_find_chunk(encap_uof_obj->obj_hdr,
						ICP_QAT_UOF_IMAG, chunk_hdr);
		अगर (!chunk_hdr)
			अवरोध;
		image = (काष्ठा icp_qat_uof_image *)(encap_uof_obj->beg_uof +
						     chunk_hdr->offset);
		ae_regtab = (काष्ठा icp_qat_uof_objtable *)
			   (image->reg_tab_offset +
			   obj_handle->obj_hdr->file_buff);
		ae_uimage[j].ae_reg_num = ae_regtab->entry_num;
		ae_uimage[j].ae_reg = (काष्ठा icp_qat_uof_ae_reg *)
			(((अक्षर *)ae_regtab) +
			माप(काष्ठा icp_qat_uof_objtable));
		init_reg_sym_tab = (काष्ठा icp_qat_uof_objtable *)
				   (image->init_reg_sym_tab +
				   obj_handle->obj_hdr->file_buff);
		ae_uimage[j].init_regsym_num = init_reg_sym_tab->entry_num;
		ae_uimage[j].init_regsym = (काष्ठा icp_qat_uof_init_regsym *)
			(((अक्षर *)init_reg_sym_tab) +
			माप(काष्ठा icp_qat_uof_objtable));
		sअवरोध_tab = (काष्ठा icp_qat_uof_objtable *)
			(image->sअवरोध_tab + obj_handle->obj_hdr->file_buff);
		ae_uimage[j].sअवरोध_num = sअवरोध_tab->entry_num;
		ae_uimage[j].sअवरोध = (काष्ठा icp_qat_uof_sअवरोध *)
				      (((अक्षर *)sअवरोध_tab) +
				      माप(काष्ठा icp_qat_uof_objtable));
		ae_uimage[j].img_ptr = image;
		अगर (qat_uclo_check_image_compat(encap_uof_obj, image))
			जाओ out_err;
		ae_uimage[j].page =
			kzalloc(माप(काष्ठा icp_qat_uclo_encap_page),
				GFP_KERNEL);
		अगर (!ae_uimage[j].page)
			जाओ out_err;
		qat_uclo_map_image_page(encap_uof_obj, image,
					ae_uimage[j].page);
	पूर्ण
	वापस j;
out_err:
	क्रम (i = 0; i < j; i++)
		kमुक्त(ae_uimage[i].page);
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_map_ae(काष्ठा icp_qat_fw_loader_handle *handle, पूर्णांक max_ae)
अणु
	पूर्णांक i, ae;
	पूर्णांक mflag = 0;
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित दीर्घ cfg_ae_mask = handle->cfg_ae_mask;

	क्रम_each_set_bit(ae, &ae_mask, max_ae) अणु
		अगर (!test_bit(ae, &cfg_ae_mask))
			जारी;

		क्रम (i = 0; i < obj_handle->uimage_num; i++) अणु
			अगर (!test_bit(ae, (अचिन्हित दीर्घ *)
			&obj_handle->ae_uimage[i].img_ptr->ae_asचिन्हित))
				जारी;
			mflag = 1;
			अगर (qat_uclo_init_ae_data(obj_handle, ae, i))
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (!mflag) अणु
		pr_err("QAT: uimage uses AE not set\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा icp_qat_uof_strtable *
qat_uclo_map_str_table(काष्ठा icp_qat_uclo_objhdr *obj_hdr,
		       अक्षर *tab_name, काष्ठा icp_qat_uof_strtable *str_table)
अणु
	काष्ठा icp_qat_uof_chunkhdr *chunk_hdr;

	chunk_hdr = qat_uclo_find_chunk((काष्ठा icp_qat_uof_objhdr *)
					obj_hdr->file_buff, tab_name, शून्य);
	अगर (chunk_hdr) अणु
		पूर्णांक hdr_size;

		स_नकल(&str_table->table_len, obj_hdr->file_buff +
		       chunk_hdr->offset, माप(str_table->table_len));
		hdr_size = (अक्षर *)&str_table->strings - (अक्षर *)str_table;
		str_table->strings = (uपूर्णांकptr_t)obj_hdr->file_buff +
					chunk_hdr->offset + hdr_size;
		वापस str_table;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
qat_uclo_map_iniपंचांगem_table(काष्ठा icp_qat_uof_encap_obj *encap_uof_obj,
			   काष्ठा icp_qat_uclo_init_mem_table *init_mem_tab)
अणु
	काष्ठा icp_qat_uof_chunkhdr *chunk_hdr;

	chunk_hdr = qat_uclo_find_chunk(encap_uof_obj->obj_hdr,
					ICP_QAT_UOF_IMEM, शून्य);
	अगर (chunk_hdr) अणु
		स_हटाओ(&init_mem_tab->entry_num, encap_uof_obj->beg_uof +
			chunk_hdr->offset, माप(अचिन्हित पूर्णांक));
		init_mem_tab->init_mem = (काष्ठा icp_qat_uof_iniपंचांगem *)
		(encap_uof_obj->beg_uof + chunk_hdr->offset +
		माप(अचिन्हित पूर्णांक));
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
qat_uclo_get_dev_type(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	चयन (handle->pci_dev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_QAT_DH895XCC:
		वापस ICP_QAT_AC_895XCC_DEV_TYPE;
	हाल PCI_DEVICE_ID_INTEL_QAT_C62X:
		वापस ICP_QAT_AC_C62X_DEV_TYPE;
	हाल PCI_DEVICE_ID_INTEL_QAT_C3XXX:
		वापस ICP_QAT_AC_C3XXX_DEV_TYPE;
	हाल ADF_4XXX_PCI_DEVICE_ID:
		वापस ICP_QAT_AC_4XXX_A_DEV_TYPE;
	शेष:
		pr_err("QAT: unsupported device 0x%x\n",
		       handle->pci_dev->device);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक qat_uclo_check_uof_compat(काष्ठा icp_qat_uclo_objhandle *obj_handle)
अणु
	अचिन्हित पूर्णांक maj_ver, prod_type = obj_handle->prod_type;

	अगर (!(prod_type & obj_handle->encap_uof_obj.obj_hdr->ac_dev_type)) अणु
		pr_err("QAT: UOF type 0x%x doesn't match with platform 0x%x\n",
		       obj_handle->encap_uof_obj.obj_hdr->ac_dev_type,
		       prod_type);
		वापस -EINVAL;
	पूर्ण
	maj_ver = obj_handle->prod_rev & 0xff;
	अगर (obj_handle->encap_uof_obj.obj_hdr->max_cpu_ver < maj_ver ||
	    obj_handle->encap_uof_obj.obj_hdr->min_cpu_ver > maj_ver) अणु
		pr_err("QAT: UOF majVer 0x%x out of range\n", maj_ver);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_init_reg(काष्ठा icp_qat_fw_loader_handle *handle,
			     अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx_mask,
			     क्रमागत icp_qat_uof_regtype reg_type,
			     अचिन्हित लघु reg_addr, अचिन्हित पूर्णांक value)
अणु
	चयन (reg_type) अणु
	हाल ICP_GPA_ABS:
	हाल ICP_GPB_ABS:
		ctx_mask = 0;
		fallthrough;
	हाल ICP_GPA_REL:
	हाल ICP_GPB_REL:
		वापस qat_hal_init_gpr(handle, ae, ctx_mask, reg_type,
					reg_addr, value);
	हाल ICP_SR_ABS:
	हाल ICP_DR_ABS:
	हाल ICP_SR_RD_ABS:
	हाल ICP_DR_RD_ABS:
		ctx_mask = 0;
		fallthrough;
	हाल ICP_SR_REL:
	हाल ICP_DR_REL:
	हाल ICP_SR_RD_REL:
	हाल ICP_DR_RD_REL:
		वापस qat_hal_init_rd_xfer(handle, ae, ctx_mask, reg_type,
					    reg_addr, value);
	हाल ICP_SR_WR_ABS:
	हाल ICP_DR_WR_ABS:
		ctx_mask = 0;
		fallthrough;
	हाल ICP_SR_WR_REL:
	हाल ICP_DR_WR_REL:
		वापस qat_hal_init_wr_xfer(handle, ae, ctx_mask, reg_type,
					    reg_addr, value);
	हाल ICP_NEIGH_REL:
		वापस qat_hal_init_nn(handle, ae, ctx_mask, reg_addr, value);
	शेष:
		pr_err("QAT: UOF uses not supported reg type 0x%x\n", reg_type);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_init_reg_sym(काष्ठा icp_qat_fw_loader_handle *handle,
				 अचिन्हित पूर्णांक ae,
				 काष्ठा icp_qat_uclo_encapme *encap_ae)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित अक्षर ctx_mask;
	काष्ठा icp_qat_uof_init_regsym *init_regsym;

	अगर (ICP_QAT_CTX_MODE(encap_ae->img_ptr->ae_mode) ==
	    ICP_QAT_UCLO_MAX_CTX)
		ctx_mask = 0xff;
	अन्यथा
		ctx_mask = 0x55;

	क्रम (i = 0; i < encap_ae->init_regsym_num; i++) अणु
		अचिन्हित पूर्णांक exp_res;

		init_regsym = &encap_ae->init_regsym[i];
		exp_res = init_regsym->value;
		चयन (init_regsym->init_type) अणु
		हाल ICP_QAT_UOF_INIT_REG:
			qat_uclo_init_reg(handle, ae, ctx_mask,
					  (क्रमागत icp_qat_uof_regtype)
					  init_regsym->reg_type,
					  (अचिन्हित लघु)init_regsym->reg_addr,
					  exp_res);
			अवरोध;
		हाल ICP_QAT_UOF_INIT_REG_CTX:
			/* check अगर ctx is appropriate क्रम the ctxMode */
			अगर (!((1 << init_regsym->ctx) & ctx_mask)) अणु
				pr_err("QAT: invalid ctx num = 0x%x\n",
				       init_regsym->ctx);
				वापस -EINVAL;
			पूर्ण
			qat_uclo_init_reg(handle, ae,
					  (अचिन्हित अक्षर)
					  (1 << init_regsym->ctx),
					  (क्रमागत icp_qat_uof_regtype)
					  init_regsym->reg_type,
					  (अचिन्हित लघु)init_regsym->reg_addr,
					  exp_res);
			अवरोध;
		हाल ICP_QAT_UOF_INIT_EXPR:
			pr_err("QAT: INIT_EXPR feature not supported\n");
			वापस -EINVAL;
		हाल ICP_QAT_UOF_INIT_EXPR_ENDIAN_SWAP:
			pr_err("QAT: INIT_EXPR_ENDIAN_SWAP feature not supported\n");
			वापस -EINVAL;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_init_globals(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	काष्ठा icp_qat_uclo_aedata *aed;
	अचिन्हित पूर्णांक s, ae;

	अगर (obj_handle->global_inited)
		वापस 0;
	अगर (obj_handle->init_mem_tab.entry_num) अणु
		अगर (qat_uclo_init_memory(handle)) अणु
			pr_err("QAT: initialize memory failed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		aed = &obj_handle->ae_data[ae];
		क्रम (s = 0; s < aed->slice_num; s++) अणु
			अगर (!aed->ae_slices[s].encap_image)
				जारी;
			अगर (qat_uclo_init_reg_sym(handle, ae, aed->ae_slices[s].encap_image))
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	obj_handle->global_inited = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक qat_hal_set_modes(काष्ठा icp_qat_fw_loader_handle *handle,
			     काष्ठा icp_qat_uclo_objhandle *obj_handle,
			     अचिन्हित अक्षर ae,
			     काष्ठा icp_qat_uof_image *uof_image)
अणु
	अचिन्हित अक्षर mode;
	पूर्णांक ret;

	mode = ICP_QAT_CTX_MODE(uof_image->ae_mode);
	ret = qat_hal_set_ae_ctx_mode(handle, ae, mode);
	अगर (ret) अणु
		pr_err("QAT: qat_hal_set_ae_ctx_mode error\n");
		वापस ret;
	पूर्ण
	अगर (handle->chip_info->nn) अणु
		mode = ICP_QAT_NN_MODE(uof_image->ae_mode);
		ret = qat_hal_set_ae_nn_mode(handle, ae, mode);
		अगर (ret) अणु
			pr_err("QAT: qat_hal_set_ae_nn_mode error\n");
			वापस ret;
		पूर्ण
	पूर्ण
	mode = ICP_QAT_LOC_MEM0_MODE(uof_image->ae_mode);
	ret = qat_hal_set_ae_lm_mode(handle, ae, ICP_LMEM0, mode);
	अगर (ret) अणु
		pr_err("QAT: qat_hal_set_ae_lm_mode LMEM0 error\n");
		वापस ret;
	पूर्ण
	mode = ICP_QAT_LOC_MEM1_MODE(uof_image->ae_mode);
	ret = qat_hal_set_ae_lm_mode(handle, ae, ICP_LMEM1, mode);
	अगर (ret) अणु
		pr_err("QAT: qat_hal_set_ae_lm_mode LMEM1 error\n");
		वापस ret;
	पूर्ण
	अगर (handle->chip_info->lm2lm3) अणु
		mode = ICP_QAT_LOC_MEM2_MODE(uof_image->ae_mode);
		ret = qat_hal_set_ae_lm_mode(handle, ae, ICP_LMEM2, mode);
		अगर (ret) अणु
			pr_err("QAT: qat_hal_set_ae_lm_mode LMEM2 error\n");
			वापस ret;
		पूर्ण
		mode = ICP_QAT_LOC_MEM3_MODE(uof_image->ae_mode);
		ret = qat_hal_set_ae_lm_mode(handle, ae, ICP_LMEM3, mode);
		अगर (ret) अणु
			pr_err("QAT: qat_hal_set_ae_lm_mode LMEM3 error\n");
			वापस ret;
		पूर्ण
		mode = ICP_QAT_LOC_TINDEX_MODE(uof_image->ae_mode);
		qat_hal_set_ae_tindex_mode(handle, ae, mode);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_set_ae_mode(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	काष्ठा icp_qat_uof_image *uof_image;
	काष्ठा icp_qat_uclo_aedata *ae_data;
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित दीर्घ cfg_ae_mask = handle->cfg_ae_mask;
	अचिन्हित अक्षर ae, s;
	पूर्णांक error;

	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		अगर (!test_bit(ae, &cfg_ae_mask))
			जारी;

		ae_data = &obj_handle->ae_data[ae];
		क्रम (s = 0; s < min_t(अचिन्हित पूर्णांक, ae_data->slice_num,
				      ICP_QAT_UCLO_MAX_CTX); s++) अणु
			अगर (!obj_handle->ae_data[ae].ae_slices[s].encap_image)
				जारी;
			uof_image = ae_data->ae_slices[s].encap_image->img_ptr;
			error = qat_hal_set_modes(handle, obj_handle, ae,
						  uof_image);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qat_uclo_init_uword_num(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	काष्ठा icp_qat_uclo_encapme *image;
	पूर्णांक a;

	क्रम (a = 0; a < obj_handle->uimage_num; a++) अणु
		image = &obj_handle->ae_uimage[a];
		image->uwords_num = image->page->beg_addr_p +
					image->page->micro_words_num;
	पूर्ण
पूर्ण

अटल पूर्णांक qat_uclo_parse_uof_obj(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित पूर्णांक ae;

	obj_handle->encap_uof_obj.beg_uof = obj_handle->obj_hdr->file_buff;
	obj_handle->encap_uof_obj.obj_hdr = (काष्ठा icp_qat_uof_objhdr *)
					     obj_handle->obj_hdr->file_buff;
	obj_handle->uword_in_bytes = 6;
	obj_handle->prod_type = qat_uclo_get_dev_type(handle);
	obj_handle->prod_rev = PID_MAJOR_REV |
			(PID_MINOR_REV & handle->hal_handle->revision_id);
	अगर (qat_uclo_check_uof_compat(obj_handle)) अणु
		pr_err("QAT: UOF incompatible\n");
		वापस -EINVAL;
	पूर्ण
	obj_handle->uword_buf = kसुस्मृति(UWORD_CPYBUF_SIZE, माप(u64),
					GFP_KERNEL);
	अगर (!obj_handle->uword_buf)
		वापस -ENOMEM;
	obj_handle->ustore_phy_size = ICP_QAT_UCLO_MAX_USTORE;
	अगर (!obj_handle->obj_hdr->file_buff ||
	    !qat_uclo_map_str_table(obj_handle->obj_hdr, ICP_QAT_UOF_STRT,
				    &obj_handle->str_table)) अणु
		pr_err("QAT: UOF doesn't have effective images\n");
		जाओ out_err;
	पूर्ण
	obj_handle->uimage_num =
		qat_uclo_map_uimage(obj_handle, obj_handle->ae_uimage,
				    ICP_QAT_UCLO_MAX_AE * ICP_QAT_UCLO_MAX_CTX);
	अगर (!obj_handle->uimage_num)
		जाओ out_err;
	अगर (qat_uclo_map_ae(handle, handle->hal_handle->ae_max_num)) अणु
		pr_err("QAT: Bad object\n");
		जाओ out_check_uof_aemask_err;
	पूर्ण
	qat_uclo_init_uword_num(handle);
	qat_uclo_map_iniपंचांगem_table(&obj_handle->encap_uof_obj,
				   &obj_handle->init_mem_tab);
	अगर (qat_uclo_set_ae_mode(handle))
		जाओ out_check_uof_aemask_err;
	वापस 0;
out_check_uof_aemask_err:
	क्रम (ae = 0; ae < obj_handle->uimage_num; ae++)
		kमुक्त(obj_handle->ae_uimage[ae].page);
out_err:
	kमुक्त(obj_handle->uword_buf);
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक qat_uclo_map_suof_file_hdr(काष्ठा icp_qat_fw_loader_handle *handle,
				      काष्ठा icp_qat_suof_filehdr *suof_ptr,
				      पूर्णांक suof_size)
अणु
	अचिन्हित पूर्णांक check_sum = 0;
	अचिन्हित पूर्णांक min_ver_offset = 0;
	काष्ठा icp_qat_suof_handle *suof_handle = handle->sobj_handle;

	suof_handle->file_id = ICP_QAT_SUOF_FID;
	suof_handle->suof_buf = (अक्षर *)suof_ptr;
	suof_handle->suof_size = suof_size;
	min_ver_offset = suof_size - दुरत्व(काष्ठा icp_qat_suof_filehdr,
					      min_ver);
	check_sum = qat_uclo_calc_str_checksum((अक्षर *)&suof_ptr->min_ver,
					       min_ver_offset);
	अगर (check_sum != suof_ptr->check_sum) अणु
		pr_err("QAT: incorrect SUOF checksum\n");
		वापस -EINVAL;
	पूर्ण
	suof_handle->check_sum = suof_ptr->check_sum;
	suof_handle->min_ver = suof_ptr->min_ver;
	suof_handle->maj_ver = suof_ptr->maj_ver;
	suof_handle->fw_type = suof_ptr->fw_type;
	वापस 0;
पूर्ण

अटल व्योम qat_uclo_map_simg(काष्ठा icp_qat_fw_loader_handle *handle,
			      काष्ठा icp_qat_suof_img_hdr *suof_img_hdr,
			      काष्ठा icp_qat_suof_chunk_hdr *suof_chunk_hdr)
अणु
	काष्ठा icp_qat_suof_handle *suof_handle = handle->sobj_handle;
	काष्ठा icp_qat_simg_ae_mode *ae_mode;
	काष्ठा icp_qat_suof_objhdr *suof_objhdr;

	suof_img_hdr->simg_buf  = (suof_handle->suof_buf +
				   suof_chunk_hdr->offset +
				   माप(*suof_objhdr));
	suof_img_hdr->simg_len = ((काष्ठा icp_qat_suof_objhdr *)(uपूर्णांकptr_t)
				  (suof_handle->suof_buf +
				   suof_chunk_hdr->offset))->img_length;

	suof_img_hdr->css_header = suof_img_hdr->simg_buf;
	suof_img_hdr->css_key = (suof_img_hdr->css_header +
				 माप(काष्ठा icp_qat_css_hdr));
	suof_img_hdr->css_signature = suof_img_hdr->css_key +
				      ICP_QAT_CSS_FWSK_MODULUS_LEN(handle) +
				      ICP_QAT_CSS_FWSK_EXPONENT_LEN(handle);
	suof_img_hdr->css_simg = suof_img_hdr->css_signature +
				 ICP_QAT_CSS_SIGNATURE_LEN(handle);

	ae_mode = (काष्ठा icp_qat_simg_ae_mode *)(suof_img_hdr->css_simg);
	suof_img_hdr->ae_mask = ae_mode->ae_mask;
	suof_img_hdr->simg_name = (अचिन्हित दीर्घ)&ae_mode->simg_name;
	suof_img_hdr->appmeta_data = (अचिन्हित दीर्घ)&ae_mode->appmeta_data;
	suof_img_hdr->fw_type = ae_mode->fw_type;
पूर्ण

अटल व्योम
qat_uclo_map_suof_symobjs(काष्ठा icp_qat_suof_handle *suof_handle,
			  काष्ठा icp_qat_suof_chunk_hdr *suof_chunk_hdr)
अणु
	अक्षर **sym_str = (अक्षर **)&suof_handle->sym_str;
	अचिन्हित पूर्णांक *sym_size = &suof_handle->sym_size;
	काष्ठा icp_qat_suof_strtable *str_table_obj;

	*sym_size = *(अचिन्हित पूर्णांक *)(uपूर्णांकptr_t)
		   (suof_chunk_hdr->offset + suof_handle->suof_buf);
	*sym_str = (अक्षर *)(uपूर्णांकptr_t)
		   (suof_handle->suof_buf + suof_chunk_hdr->offset +
		   माप(str_table_obj->tab_length));
पूर्ण

अटल पूर्णांक qat_uclo_check_simg_compat(काष्ठा icp_qat_fw_loader_handle *handle,
				      काष्ठा icp_qat_suof_img_hdr *img_hdr)
अणु
	काष्ठा icp_qat_simg_ae_mode *img_ae_mode = शून्य;
	अचिन्हित पूर्णांक prod_rev, maj_ver, prod_type;

	prod_type = qat_uclo_get_dev_type(handle);
	img_ae_mode = (काष्ठा icp_qat_simg_ae_mode *)img_hdr->css_simg;
	prod_rev = PID_MAJOR_REV |
			 (PID_MINOR_REV & handle->hal_handle->revision_id);
	अगर (img_ae_mode->dev_type != prod_type) अणु
		pr_err("QAT: incompatible product type %x\n",
		       img_ae_mode->dev_type);
		वापस -EINVAL;
	पूर्ण
	maj_ver = prod_rev & 0xff;
	अगर (maj_ver > img_ae_mode->devmax_ver ||
	    maj_ver < img_ae_mode->devmin_ver) अणु
		pr_err("QAT: incompatible device majver 0x%x\n", maj_ver);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qat_uclo_del_suof(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	काष्ठा icp_qat_suof_handle *sobj_handle = handle->sobj_handle;

	kमुक्त(sobj_handle->img_table.simg_hdr);
	sobj_handle->img_table.simg_hdr = शून्य;
	kमुक्त(handle->sobj_handle);
	handle->sobj_handle = शून्य;
पूर्ण

अटल व्योम qat_uclo_tail_img(काष्ठा icp_qat_suof_img_hdr *suof_img_hdr,
			      अचिन्हित पूर्णांक img_id, अचिन्हित पूर्णांक num_simgs)
अणु
	काष्ठा icp_qat_suof_img_hdr img_header;

	अगर (img_id != num_simgs - 1) अणु
		स_नकल(&img_header, &suof_img_hdr[num_simgs - 1],
		       माप(*suof_img_hdr));
		स_नकल(&suof_img_hdr[num_simgs - 1], &suof_img_hdr[img_id],
		       माप(*suof_img_hdr));
		स_नकल(&suof_img_hdr[img_id], &img_header,
		       माप(*suof_img_hdr));
	पूर्ण
पूर्ण

अटल पूर्णांक qat_uclo_map_suof(काष्ठा icp_qat_fw_loader_handle *handle,
			     काष्ठा icp_qat_suof_filehdr *suof_ptr,
			     पूर्णांक suof_size)
अणु
	काष्ठा icp_qat_suof_handle *suof_handle = handle->sobj_handle;
	काष्ठा icp_qat_suof_chunk_hdr *suof_chunk_hdr = शून्य;
	काष्ठा icp_qat_suof_img_hdr *suof_img_hdr = शून्य;
	पूर्णांक ret = 0, ae0_img = ICP_QAT_UCLO_MAX_AE;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा icp_qat_suof_img_hdr img_header;

	अगर (!suof_ptr || suof_size == 0) अणु
		pr_err("QAT: input parameter SUOF pointer/size is NULL\n");
		वापस -EINVAL;
	पूर्ण
	अगर (qat_uclo_check_suof_क्रमmat(suof_ptr))
		वापस -EINVAL;
	ret = qat_uclo_map_suof_file_hdr(handle, suof_ptr, suof_size);
	अगर (ret)
		वापस ret;
	suof_chunk_hdr = (काष्ठा icp_qat_suof_chunk_hdr *)
			 ((uपूर्णांकptr_t)suof_ptr + माप(*suof_ptr));

	qat_uclo_map_suof_symobjs(suof_handle, suof_chunk_hdr);
	suof_handle->img_table.num_simgs = suof_ptr->num_chunks - 1;

	अगर (suof_handle->img_table.num_simgs != 0) अणु
		suof_img_hdr = kसुस्मृति(suof_handle->img_table.num_simgs,
				       माप(img_header),
				       GFP_KERNEL);
		अगर (!suof_img_hdr)
			वापस -ENOMEM;
		suof_handle->img_table.simg_hdr = suof_img_hdr;

		क्रम (i = 0; i < suof_handle->img_table.num_simgs; i++) अणु
			qat_uclo_map_simg(handle, &suof_img_hdr[i],
					  &suof_chunk_hdr[1 + i]);
			ret = qat_uclo_check_simg_compat(handle,
							 &suof_img_hdr[i]);
			अगर (ret)
				वापस ret;
			suof_img_hdr[i].ae_mask &= handle->cfg_ae_mask;
			अगर ((suof_img_hdr[i].ae_mask & 0x1) != 0)
				ae0_img = i;
		पूर्ण

		अगर (!handle->chip_info->tgroup_share_ustore) अणु
			qat_uclo_tail_img(suof_img_hdr, ae0_img,
					  suof_handle->img_table.num_simgs);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा ADD_ADDR(high, low)  ((((u64)high) << 32) + low)
#घोषणा BITS_IN_DWORD 32

अटल पूर्णांक qat_uclo_auth_fw(काष्ठा icp_qat_fw_loader_handle *handle,
			    काष्ठा icp_qat_fw_auth_desc *desc)
अणु
	u32 fcu_sts, retry = 0;
	u32 fcu_ctl_csr, fcu_sts_csr;
	u32 fcu_dram_hi_csr, fcu_dram_lo_csr;
	u64 bus_addr;

	bus_addr = ADD_ADDR(desc->css_hdr_high, desc->css_hdr_low)
			   - माप(काष्ठा icp_qat_auth_chunk);

	fcu_ctl_csr = handle->chip_info->fcu_ctl_csr;
	fcu_sts_csr = handle->chip_info->fcu_sts_csr;
	fcu_dram_hi_csr = handle->chip_info->fcu_dram_addr_hi;
	fcu_dram_lo_csr = handle->chip_info->fcu_dram_addr_lo;

	SET_CAP_CSR(handle, fcu_dram_hi_csr, (bus_addr >> BITS_IN_DWORD));
	SET_CAP_CSR(handle, fcu_dram_lo_csr, bus_addr);
	SET_CAP_CSR(handle, fcu_ctl_csr, FCU_CTRL_CMD_AUTH);

	करो अणु
		msleep(FW_AUTH_WAIT_PERIOD);
		fcu_sts = GET_CAP_CSR(handle, fcu_sts_csr);
		अगर ((fcu_sts & FCU_AUTH_STS_MASK) == FCU_STS_VERI_FAIL)
			जाओ auth_fail;
		अगर (((fcu_sts >> FCU_STS_AUTHFWLD_POS) & 0x1))
			अगर ((fcu_sts & FCU_AUTH_STS_MASK) == FCU_STS_VERI_DONE)
				वापस 0;
	पूर्ण जबतक (retry++ < FW_AUTH_MAX_RETRY);
auth_fail:
	pr_err("QAT: authentication error (FCU_STATUS = 0x%x),retry = %d\n",
	       fcu_sts & FCU_AUTH_STS_MASK, retry);
	वापस -EINVAL;
पूर्ण

अटल bool qat_uclo_is_broadcast(काष्ठा icp_qat_fw_loader_handle *handle,
				  पूर्णांक imgid)
अणु
	काष्ठा icp_qat_suof_handle *sobj_handle;

	अगर (!handle->chip_info->tgroup_share_ustore)
		वापस false;

	sobj_handle = (काष्ठा icp_qat_suof_handle *)handle->sobj_handle;
	अगर (handle->hal_handle->admin_ae_mask &
	    sobj_handle->img_table.simg_hdr[imgid].ae_mask)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक qat_uclo_broadcast_load_fw(काष्ठा icp_qat_fw_loader_handle *handle,
				      काष्ठा icp_qat_fw_auth_desc *desc)
अणु
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित दीर्घ desc_ae_mask = desc->ae_mask;
	u32 fcu_sts, ae_broadcast_mask = 0;
	u32 fcu_loaded_csr, ae_loaded;
	u32 fcu_sts_csr, fcu_ctl_csr;
	अचिन्हित पूर्णांक ae, retry = 0;

	अगर (handle->chip_info->tgroup_share_ustore) अणु
		fcu_ctl_csr = handle->chip_info->fcu_ctl_csr;
		fcu_sts_csr = handle->chip_info->fcu_sts_csr;
		fcu_loaded_csr = handle->chip_info->fcu_loaded_ae_csr;
	पूर्ण अन्यथा अणु
		pr_err("Chip 0x%x doesn't support broadcast load\n",
		       handle->pci_dev->device);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		अगर (qat_hal_check_ae_active(handle, (अचिन्हित अक्षर)ae)) अणु
			pr_err("QAT: Broadcast load failed. AE is not enabled or active.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (test_bit(ae, &desc_ae_mask))
			ae_broadcast_mask |= 1 << ae;
	पूर्ण

	अगर (ae_broadcast_mask) अणु
		SET_CAP_CSR(handle, FCU_ME_BROADCAST_MASK_TYPE,
			    ae_broadcast_mask);

		SET_CAP_CSR(handle, fcu_ctl_csr, FCU_CTRL_CMD_LOAD);

		करो अणु
			msleep(FW_AUTH_WAIT_PERIOD);
			fcu_sts = GET_CAP_CSR(handle, fcu_sts_csr);
			fcu_sts &= FCU_AUTH_STS_MASK;

			अगर (fcu_sts == FCU_STS_LOAD_FAIL) अणु
				pr_err("Broadcast load failed: 0x%x)\n", fcu_sts);
				वापस -EINVAL;
			पूर्ण अन्यथा अगर (fcu_sts == FCU_STS_LOAD_DONE) अणु
				ae_loaded = GET_CAP_CSR(handle, fcu_loaded_csr);
				ae_loaded >>= handle->chip_info->fcu_loaded_ae_pos;

				अगर ((ae_loaded & ae_broadcast_mask) == ae_broadcast_mask)
					अवरोध;
			पूर्ण
		पूर्ण जबतक (retry++ < FW_AUTH_MAX_RETRY);

		अगर (retry > FW_AUTH_MAX_RETRY) अणु
			pr_err("QAT: broadcast load failed timeout %d\n", retry);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_simg_alloc(काष्ठा icp_qat_fw_loader_handle *handle,
			       काष्ठा icp_firml_dram_desc *dram_desc,
			       अचिन्हित पूर्णांक size)
अणु
	व्योम *vptr;
	dma_addr_t ptr;

	vptr = dma_alloc_coherent(&handle->pci_dev->dev,
				  size, &ptr, GFP_KERNEL);
	अगर (!vptr)
		वापस -ENOMEM;
	dram_desc->dram_base_addr_v = vptr;
	dram_desc->dram_bus_addr = ptr;
	dram_desc->dram_size = size;
	वापस 0;
पूर्ण

अटल व्योम qat_uclo_simg_मुक्त(काष्ठा icp_qat_fw_loader_handle *handle,
			       काष्ठा icp_firml_dram_desc *dram_desc)
अणु
	अगर (handle && dram_desc && dram_desc->dram_base_addr_v) अणु
		dma_मुक्त_coherent(&handle->pci_dev->dev,
				  (माप_प्रकार)(dram_desc->dram_size),
				  dram_desc->dram_base_addr_v,
				  dram_desc->dram_bus_addr);
	पूर्ण

	अगर (dram_desc)
		स_रखो(dram_desc, 0, माप(*dram_desc));
पूर्ण

अटल व्योम qat_uclo_ummap_auth_fw(काष्ठा icp_qat_fw_loader_handle *handle,
				   काष्ठा icp_qat_fw_auth_desc **desc)
अणु
	काष्ठा icp_firml_dram_desc dram_desc;

	अगर (*desc) अणु
		dram_desc.dram_base_addr_v = *desc;
		dram_desc.dram_bus_addr = ((काष्ठा icp_qat_auth_chunk *)
					   (*desc))->chunk_bus_addr;
		dram_desc.dram_size = ((काष्ठा icp_qat_auth_chunk *)
				       (*desc))->chunk_size;
		qat_uclo_simg_मुक्त(handle, &dram_desc);
	पूर्ण
पूर्ण

अटल पूर्णांक qat_uclo_map_auth_fw(काष्ठा icp_qat_fw_loader_handle *handle,
				अक्षर *image, अचिन्हित पूर्णांक size,
				काष्ठा icp_qat_fw_auth_desc **desc)
अणु
	काष्ठा icp_qat_css_hdr *css_hdr = (काष्ठा icp_qat_css_hdr *)image;
	काष्ठा icp_qat_fw_auth_desc *auth_desc;
	काष्ठा icp_qat_auth_chunk *auth_chunk;
	u64 virt_addr,  bus_addr, virt_base;
	अचिन्हित पूर्णांक length, simg_offset = माप(*auth_chunk);
	काष्ठा icp_qat_simg_ae_mode *simg_ae_mode;
	काष्ठा icp_firml_dram_desc img_desc;

	अगर (size > (ICP_QAT_AE_IMG_OFFSET(handle) + ICP_QAT_CSS_MAX_IMAGE_LEN)) अणु
		pr_err("QAT: error, input image size overflow %d\n", size);
		वापस -EINVAL;
	पूर्ण
	length = (css_hdr->fw_type == CSS_AE_FIRMWARE) ?
		 ICP_QAT_CSS_AE_SIMG_LEN(handle) + simg_offset :
		 size + ICP_QAT_CSS_FWSK_PAD_LEN(handle) + simg_offset;
	अगर (qat_uclo_simg_alloc(handle, &img_desc, length)) अणु
		pr_err("QAT: error, allocate continuous dram fail\n");
		वापस -ENOMEM;
	पूर्ण

	auth_chunk = img_desc.dram_base_addr_v;
	auth_chunk->chunk_size = img_desc.dram_size;
	auth_chunk->chunk_bus_addr = img_desc.dram_bus_addr;
	virt_base = (uपूर्णांकptr_t)img_desc.dram_base_addr_v + simg_offset;
	bus_addr  = img_desc.dram_bus_addr + simg_offset;
	auth_desc = img_desc.dram_base_addr_v;
	auth_desc->css_hdr_high = (अचिन्हित पूर्णांक)(bus_addr >> BITS_IN_DWORD);
	auth_desc->css_hdr_low = (अचिन्हित पूर्णांक)bus_addr;
	virt_addr = virt_base;

	स_नकल((व्योम *)(uपूर्णांकptr_t)virt_addr, image, माप(*css_hdr));
	/* pub key */
	bus_addr = ADD_ADDR(auth_desc->css_hdr_high, auth_desc->css_hdr_low) +
			   माप(*css_hdr);
	virt_addr = virt_addr + माप(*css_hdr);

	auth_desc->fwsk_pub_high = (अचिन्हित पूर्णांक)(bus_addr >> BITS_IN_DWORD);
	auth_desc->fwsk_pub_low = (अचिन्हित पूर्णांक)bus_addr;

	स_नकल((व्योम *)(uपूर्णांकptr_t)virt_addr,
	       (व्योम *)(image + माप(*css_hdr)),
	       ICP_QAT_CSS_FWSK_MODULUS_LEN(handle));
	/* padding */
	स_रखो((व्योम *)(uपूर्णांकptr_t)(virt_addr + ICP_QAT_CSS_FWSK_MODULUS_LEN(handle)),
	       0, ICP_QAT_CSS_FWSK_PAD_LEN(handle));

	/* exponent */
	स_नकल((व्योम *)(uपूर्णांकptr_t)(virt_addr + ICP_QAT_CSS_FWSK_MODULUS_LEN(handle) +
	       ICP_QAT_CSS_FWSK_PAD_LEN(handle)),
	       (व्योम *)(image + माप(*css_hdr) +
			ICP_QAT_CSS_FWSK_MODULUS_LEN(handle)),
	       माप(अचिन्हित पूर्णांक));

	/* signature */
	bus_addr = ADD_ADDR(auth_desc->fwsk_pub_high,
			    auth_desc->fwsk_pub_low) +
		   ICP_QAT_CSS_FWSK_PUB_LEN(handle);
	virt_addr = virt_addr + ICP_QAT_CSS_FWSK_PUB_LEN(handle);
	auth_desc->signature_high = (अचिन्हित पूर्णांक)(bus_addr >> BITS_IN_DWORD);
	auth_desc->signature_low = (अचिन्हित पूर्णांक)bus_addr;

	स_नकल((व्योम *)(uपूर्णांकptr_t)virt_addr,
	       (व्योम *)(image + माप(*css_hdr) +
	       ICP_QAT_CSS_FWSK_MODULUS_LEN(handle) +
	       ICP_QAT_CSS_FWSK_EXPONENT_LEN(handle)),
	       ICP_QAT_CSS_SIGNATURE_LEN(handle));

	bus_addr = ADD_ADDR(auth_desc->signature_high,
			    auth_desc->signature_low) +
		   ICP_QAT_CSS_SIGNATURE_LEN(handle);
	virt_addr += ICP_QAT_CSS_SIGNATURE_LEN(handle);

	auth_desc->img_high = (अचिन्हित पूर्णांक)(bus_addr >> BITS_IN_DWORD);
	auth_desc->img_low = (अचिन्हित पूर्णांक)bus_addr;
	auth_desc->img_len = size - ICP_QAT_AE_IMG_OFFSET(handle);
	स_नकल((व्योम *)(uपूर्णांकptr_t)virt_addr,
	       (व्योम *)(image + ICP_QAT_AE_IMG_OFFSET(handle)),
	       auth_desc->img_len);
	virt_addr = virt_base;
	/* AE firmware */
	अगर (((काष्ठा icp_qat_css_hdr *)(uपूर्णांकptr_t)virt_addr)->fw_type ==
	    CSS_AE_FIRMWARE) अणु
		auth_desc->img_ae_mode_data_high = auth_desc->img_high;
		auth_desc->img_ae_mode_data_low = auth_desc->img_low;
		bus_addr = ADD_ADDR(auth_desc->img_ae_mode_data_high,
				    auth_desc->img_ae_mode_data_low) +
			   माप(काष्ठा icp_qat_simg_ae_mode);

		auth_desc->img_ae_init_data_high = (अचिन्हित पूर्णांक)
						 (bus_addr >> BITS_IN_DWORD);
		auth_desc->img_ae_init_data_low = (अचिन्हित पूर्णांक)bus_addr;
		bus_addr += ICP_QAT_SIMG_AE_INIT_SEQ_LEN;
		auth_desc->img_ae_insts_high = (अचिन्हित पूर्णांक)
					     (bus_addr >> BITS_IN_DWORD);
		auth_desc->img_ae_insts_low = (अचिन्हित पूर्णांक)bus_addr;
		virt_addr += माप(काष्ठा icp_qat_css_hdr);
		virt_addr += ICP_QAT_CSS_FWSK_PUB_LEN(handle);
		virt_addr += ICP_QAT_CSS_SIGNATURE_LEN(handle);
		simg_ae_mode = (काष्ठा icp_qat_simg_ae_mode *)(uपूर्णांकptr_t)virt_addr;
		auth_desc->ae_mask = simg_ae_mode->ae_mask & handle->cfg_ae_mask;
	पूर्ण अन्यथा अणु
		auth_desc->img_ae_insts_high = auth_desc->img_high;
		auth_desc->img_ae_insts_low = auth_desc->img_low;
	पूर्ण
	*desc = auth_desc;
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_load_fw(काष्ठा icp_qat_fw_loader_handle *handle,
			    काष्ठा icp_qat_fw_auth_desc *desc)
अणु
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	u32 fcu_sts_csr, fcu_ctl_csr;
	u32 loaded_aes, loaded_csr;
	अचिन्हित पूर्णांक i;
	u32 fcu_sts;

	fcu_ctl_csr = handle->chip_info->fcu_ctl_csr;
	fcu_sts_csr = handle->chip_info->fcu_sts_csr;
	loaded_csr = handle->chip_info->fcu_loaded_ae_csr;

	क्रम_each_set_bit(i, &ae_mask, handle->hal_handle->ae_max_num) अणु
		पूर्णांक retry = 0;

		अगर (!((desc->ae_mask >> i) & 0x1))
			जारी;
		अगर (qat_hal_check_ae_active(handle, i)) अणु
			pr_err("QAT: AE %d is active\n", i);
			वापस -EINVAL;
		पूर्ण
		SET_CAP_CSR(handle, fcu_ctl_csr,
			    (FCU_CTRL_CMD_LOAD |
			    (1 << FCU_CTRL_BROADCAST_POS) |
			    (i << FCU_CTRL_AE_POS)));

		करो अणु
			msleep(FW_AUTH_WAIT_PERIOD);
			fcu_sts = GET_CAP_CSR(handle, fcu_sts_csr);
			अगर ((fcu_sts & FCU_AUTH_STS_MASK) ==
			    FCU_STS_LOAD_DONE) अणु
				loaded_aes = GET_CAP_CSR(handle, loaded_csr);
				loaded_aes >>= handle->chip_info->fcu_loaded_ae_pos;
				अगर (loaded_aes & (1 << i))
					अवरोध;
			पूर्ण
		पूर्ण जबतक (retry++ < FW_AUTH_MAX_RETRY);
		अगर (retry > FW_AUTH_MAX_RETRY) अणु
			pr_err("QAT: firmware load failed timeout %x\n", retry);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_map_suof_obj(काष्ठा icp_qat_fw_loader_handle *handle,
				 व्योम *addr_ptr, पूर्णांक mem_size)
अणु
	काष्ठा icp_qat_suof_handle *suof_handle;

	suof_handle = kzalloc(माप(*suof_handle), GFP_KERNEL);
	अगर (!suof_handle)
		वापस -ENOMEM;
	handle->sobj_handle = suof_handle;
	अगर (qat_uclo_map_suof(handle, addr_ptr, mem_size)) अणु
		qat_uclo_del_suof(handle);
		pr_err("QAT: map SUOF failed\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qat_uclo_wr_mimage(काष्ठा icp_qat_fw_loader_handle *handle,
		       व्योम *addr_ptr, पूर्णांक mem_size)
अणु
	काष्ठा icp_qat_fw_auth_desc *desc = शून्य;
	पूर्णांक status = 0;

	अगर (handle->chip_info->fw_auth) अणु
		अगर (!qat_uclo_map_auth_fw(handle, addr_ptr, mem_size, &desc))
			status = qat_uclo_auth_fw(handle, desc);
		qat_uclo_ummap_auth_fw(handle, &desc);
	पूर्ण अन्यथा अणु
		अगर (!handle->chip_info->sram_visible) अणु
			dev_dbg(&handle->pci_dev->dev,
				"QAT MMP fw not loaded for device 0x%x",
				handle->pci_dev->device);
			वापस status;
		पूर्ण
		qat_uclo_wr_sram_by_words(handle, 0, addr_ptr, mem_size);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक qat_uclo_map_uof_obj(काष्ठा icp_qat_fw_loader_handle *handle,
				व्योम *addr_ptr, पूर्णांक mem_size)
अणु
	काष्ठा icp_qat_uof_filehdr *filehdr;
	काष्ठा icp_qat_uclo_objhandle *objhdl;

	objhdl = kzalloc(माप(*objhdl), GFP_KERNEL);
	अगर (!objhdl)
		वापस -ENOMEM;
	objhdl->obj_buf = kmemdup(addr_ptr, mem_size, GFP_KERNEL);
	अगर (!objhdl->obj_buf)
		जाओ out_objbuf_err;
	filehdr = (काष्ठा icp_qat_uof_filehdr *)objhdl->obj_buf;
	अगर (qat_uclo_check_uof_क्रमmat(filehdr))
		जाओ out_objhdr_err;
	objhdl->obj_hdr = qat_uclo_map_chunk((अक्षर *)objhdl->obj_buf, filehdr,
					     ICP_QAT_UOF_OBJS);
	अगर (!objhdl->obj_hdr) अणु
		pr_err("QAT: object file chunk is null\n");
		जाओ out_objhdr_err;
	पूर्ण
	handle->obj_handle = objhdl;
	अगर (qat_uclo_parse_uof_obj(handle))
		जाओ out_overlay_obj_err;
	वापस 0;

out_overlay_obj_err:
	handle->obj_handle = शून्य;
	kमुक्त(objhdl->obj_hdr);
out_objhdr_err:
	kमुक्त(objhdl->obj_buf);
out_objbuf_err:
	kमुक्त(objhdl);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक qat_uclo_map_mof_file_hdr(काष्ठा icp_qat_fw_loader_handle *handle,
				     काष्ठा icp_qat_mof_file_hdr *mof_ptr,
				     u32 mof_size)
अणु
	काष्ठा icp_qat_mof_handle *mobj_handle = handle->mobj_handle;
	अचिन्हित पूर्णांक min_ver_offset;
	अचिन्हित पूर्णांक checksum;

	mobj_handle->file_id = ICP_QAT_MOF_FID;
	mobj_handle->mof_buf = (अक्षर *)mof_ptr;
	mobj_handle->mof_size = mof_size;

	min_ver_offset = mof_size - दुरत्व(काष्ठा icp_qat_mof_file_hdr,
					     min_ver);
	checksum = qat_uclo_calc_str_checksum(&mof_ptr->min_ver,
					      min_ver_offset);
	अगर (checksum != mof_ptr->checksum) अणु
		pr_err("QAT: incorrect MOF checksum\n");
		वापस -EINVAL;
	पूर्ण

	mobj_handle->checksum = mof_ptr->checksum;
	mobj_handle->min_ver = mof_ptr->min_ver;
	mobj_handle->maj_ver = mof_ptr->maj_ver;
	वापस 0;
पूर्ण

अटल व्योम qat_uclo_del_mof(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	काष्ठा icp_qat_mof_handle *mobj_handle = handle->mobj_handle;

	kमुक्त(mobj_handle->obj_table.obj_hdr);
	mobj_handle->obj_table.obj_hdr = शून्य;
	kमुक्त(handle->mobj_handle);
	handle->mobj_handle = शून्य;
पूर्ण

अटल पूर्णांक qat_uclo_seek_obj_inside_mof(काष्ठा icp_qat_mof_handle *mobj_handle,
					अक्षर *obj_name, अक्षर **obj_ptr,
					अचिन्हित पूर्णांक *obj_size)
अणु
	काष्ठा icp_qat_mof_objhdr *obj_hdr = mobj_handle->obj_table.obj_hdr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mobj_handle->obj_table.num_objs; i++) अणु
		अगर (!म_भेदन(obj_hdr[i].obj_name, obj_name,
			     ICP_QAT_SUOF_OBJ_NAME_LEN)) अणु
			*obj_ptr  = obj_hdr[i].obj_buf;
			*obj_size = obj_hdr[i].obj_size;
			वापस 0;
		पूर्ण
	पूर्ण

	pr_err("QAT: object %s is not found inside MOF\n", obj_name);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qat_uclo_map_obj_from_mof(काष्ठा icp_qat_mof_handle *mobj_handle,
				     काष्ठा icp_qat_mof_objhdr *mobj_hdr,
				     काष्ठा icp_qat_mof_obj_chunkhdr *obj_chunkhdr)
अणु
	u8 *obj;

	अगर (!म_भेदन(obj_chunkhdr->chunk_id, ICP_QAT_UOF_IMAG,
		     ICP_QAT_MOF_OBJ_CHUNKID_LEN)) अणु
		obj = mobj_handle->uobjs_hdr + obj_chunkhdr->offset;
	पूर्ण अन्यथा अगर (!म_भेदन(obj_chunkhdr->chunk_id, ICP_QAT_SUOF_IMAG,
			    ICP_QAT_MOF_OBJ_CHUNKID_LEN)) अणु
		obj = mobj_handle->sobjs_hdr + obj_chunkhdr->offset;
	पूर्ण अन्यथा अणु
		pr_err("QAT: unsupported chunk id\n");
		वापस -EINVAL;
	पूर्ण
	mobj_hdr->obj_buf = obj;
	mobj_hdr->obj_size = (अचिन्हित पूर्णांक)obj_chunkhdr->size;
	mobj_hdr->obj_name = obj_chunkhdr->name + mobj_handle->sym_str;
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_map_objs_from_mof(काष्ठा icp_qat_mof_handle *mobj_handle)
अणु
	काष्ठा icp_qat_mof_obj_chunkhdr *uobj_chunkhdr;
	काष्ठा icp_qat_mof_obj_chunkhdr *sobj_chunkhdr;
	काष्ठा icp_qat_mof_obj_hdr *uobj_hdr;
	काष्ठा icp_qat_mof_obj_hdr *sobj_hdr;
	काष्ठा icp_qat_mof_objhdr *mobj_hdr;
	अचिन्हित पूर्णांक uobj_chunk_num = 0;
	अचिन्हित पूर्णांक sobj_chunk_num = 0;
	अचिन्हित पूर्णांक *valid_chunk;
	पूर्णांक ret, i;

	uobj_hdr = (काष्ठा icp_qat_mof_obj_hdr *)mobj_handle->uobjs_hdr;
	sobj_hdr = (काष्ठा icp_qat_mof_obj_hdr *)mobj_handle->sobjs_hdr;
	अगर (uobj_hdr)
		uobj_chunk_num = uobj_hdr->num_chunks;
	अगर (sobj_hdr)
		sobj_chunk_num = sobj_hdr->num_chunks;

	mobj_hdr = kzalloc((uobj_chunk_num + sobj_chunk_num) *
			   माप(*mobj_hdr), GFP_KERNEL);
	अगर (!mobj_hdr)
		वापस -ENOMEM;

	mobj_handle->obj_table.obj_hdr = mobj_hdr;
	valid_chunk = &mobj_handle->obj_table.num_objs;
	uobj_chunkhdr = (काष्ठा icp_qat_mof_obj_chunkhdr *)
			 ((uपूर्णांकptr_t)uobj_hdr + माप(*uobj_hdr));
	sobj_chunkhdr = (काष्ठा icp_qat_mof_obj_chunkhdr *)
			((uपूर्णांकptr_t)sobj_hdr + माप(*sobj_hdr));

	/* map uof objects */
	क्रम (i = 0; i < uobj_chunk_num; i++) अणु
		ret = qat_uclo_map_obj_from_mof(mobj_handle,
						&mobj_hdr[*valid_chunk],
						&uobj_chunkhdr[i]);
		अगर (ret)
			वापस ret;
		(*valid_chunk)++;
	पूर्ण

	/* map suof objects */
	क्रम (i = 0; i < sobj_chunk_num; i++) अणु
		ret = qat_uclo_map_obj_from_mof(mobj_handle,
						&mobj_hdr[*valid_chunk],
						&sobj_chunkhdr[i]);
		अगर (ret)
			वापस ret;
		(*valid_chunk)++;
	पूर्ण

	अगर ((uobj_chunk_num + sobj_chunk_num) != *valid_chunk) अणु
		pr_err("QAT: inconsistent UOF/SUOF chunk amount\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qat_uclo_map_mof_symobjs(काष्ठा icp_qat_mof_handle *mobj_handle,
				     काष्ठा icp_qat_mof_chunkhdr *mof_chunkhdr)
अणु
	अक्षर **sym_str = (अक्षर **)&mobj_handle->sym_str;
	अचिन्हित पूर्णांक *sym_size = &mobj_handle->sym_size;
	काष्ठा icp_qat_mof_str_table *str_table_obj;

	*sym_size = *(अचिन्हित पूर्णांक *)(uपूर्णांकptr_t)
		    (mof_chunkhdr->offset + mobj_handle->mof_buf);
	*sym_str = (अक्षर *)(uपूर्णांकptr_t)
		   (mobj_handle->mof_buf + mof_chunkhdr->offset +
		    माप(str_table_obj->tab_len));
पूर्ण

अटल व्योम qat_uclo_map_mof_chunk(काष्ठा icp_qat_mof_handle *mobj_handle,
				   काष्ठा icp_qat_mof_chunkhdr *mof_chunkhdr)
अणु
	अक्षर *chunk_id = mof_chunkhdr->chunk_id;

	अगर (!म_भेदन(chunk_id, ICP_QAT_MOF_SYM_OBJS, ICP_QAT_MOF_OBJ_ID_LEN))
		qat_uclo_map_mof_symobjs(mobj_handle, mof_chunkhdr);
	अन्यथा अगर (!म_भेदन(chunk_id, ICP_QAT_UOF_OBJS, ICP_QAT_MOF_OBJ_ID_LEN))
		mobj_handle->uobjs_hdr = mobj_handle->mof_buf +
					 mof_chunkhdr->offset;
	अन्यथा अगर (!म_भेदन(chunk_id, ICP_QAT_SUOF_OBJS, ICP_QAT_MOF_OBJ_ID_LEN))
		mobj_handle->sobjs_hdr = mobj_handle->mof_buf +
					 mof_chunkhdr->offset;
पूर्ण

अटल पूर्णांक qat_uclo_check_mof_क्रमmat(काष्ठा icp_qat_mof_file_hdr *mof_hdr)
अणु
	पूर्णांक maj = mof_hdr->maj_ver & 0xff;
	पूर्णांक min = mof_hdr->min_ver & 0xff;

	अगर (mof_hdr->file_id != ICP_QAT_MOF_FID) अणु
		pr_err("QAT: invalid header 0x%x\n", mof_hdr->file_id);
		वापस -EINVAL;
	पूर्ण

	अगर (mof_hdr->num_chunks <= 0x1) अणु
		pr_err("QAT: MOF chunk amount is incorrect\n");
		वापस -EINVAL;
	पूर्ण
	अगर (maj != ICP_QAT_MOF_MAJVER || min != ICP_QAT_MOF_MINVER) अणु
		pr_err("QAT: bad MOF version, major 0x%x, minor 0x%x\n",
		       maj, min);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_uclo_map_mof_obj(काष्ठा icp_qat_fw_loader_handle *handle,
				काष्ठा icp_qat_mof_file_hdr *mof_ptr,
				u32 mof_size, अक्षर *obj_name, अक्षर **obj_ptr,
				अचिन्हित पूर्णांक *obj_size)
अणु
	काष्ठा icp_qat_mof_chunkhdr *mof_chunkhdr;
	अचिन्हित पूर्णांक file_id = mof_ptr->file_id;
	काष्ठा icp_qat_mof_handle *mobj_handle;
	अचिन्हित लघु chunks_num;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (file_id == ICP_QAT_UOF_FID || file_id == ICP_QAT_SUOF_FID) अणु
		अगर (obj_ptr)
			*obj_ptr = (अक्षर *)mof_ptr;
		अगर (obj_size)
			*obj_size = mof_size;
		वापस 0;
	पूर्ण
	अगर (qat_uclo_check_mof_क्रमmat(mof_ptr))
		वापस -EINVAL;

	mobj_handle = kzalloc(माप(*mobj_handle), GFP_KERNEL);
	अगर (!mobj_handle)
		वापस -ENOMEM;

	handle->mobj_handle = mobj_handle;
	ret = qat_uclo_map_mof_file_hdr(handle, mof_ptr, mof_size);
	अगर (ret)
		वापस ret;

	mof_chunkhdr = (व्योम *)mof_ptr + माप(*mof_ptr);
	chunks_num = mof_ptr->num_chunks;

	/* Parse MOF file chunks */
	क्रम (i = 0; i < chunks_num; i++)
		qat_uclo_map_mof_chunk(mobj_handle, &mof_chunkhdr[i]);

	/* All sym_objs uobjs and sobjs should be available */
	अगर (!mobj_handle->sym_str ||
	    (!mobj_handle->uobjs_hdr && !mobj_handle->sobjs_hdr))
		वापस -EINVAL;

	ret = qat_uclo_map_objs_from_mof(mobj_handle);
	अगर (ret)
		वापस ret;

	/* Seek specअगरied uof object in MOF */
	वापस qat_uclo_seek_obj_inside_mof(mobj_handle, obj_name,
					    obj_ptr, obj_size);
पूर्ण

पूर्णांक qat_uclo_map_obj(काष्ठा icp_qat_fw_loader_handle *handle,
		     व्योम *addr_ptr, u32 mem_size, अक्षर *obj_name)
अणु
	अक्षर *obj_addr;
	u32 obj_size;
	पूर्णांक ret;

	BUILD_BUG_ON(ICP_QAT_UCLO_MAX_AE >=
		     (माप(handle->hal_handle->ae_mask) * 8));

	अगर (!handle || !addr_ptr || mem_size < 24)
		वापस -EINVAL;

	अगर (obj_name) अणु
		ret = qat_uclo_map_mof_obj(handle, addr_ptr, mem_size, obj_name,
					   &obj_addr, &obj_size);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		obj_addr = addr_ptr;
		obj_size = mem_size;
	पूर्ण

	वापस (handle->chip_info->fw_auth) ?
			qat_uclo_map_suof_obj(handle, obj_addr, obj_size) :
			qat_uclo_map_uof_obj(handle, obj_addr, obj_size);
पूर्ण

व्योम qat_uclo_del_obj(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित पूर्णांक a;

	अगर (handle->mobj_handle)
		qat_uclo_del_mof(handle);
	अगर (handle->sobj_handle)
		qat_uclo_del_suof(handle);
	अगर (!obj_handle)
		वापस;

	kमुक्त(obj_handle->uword_buf);
	क्रम (a = 0; a < obj_handle->uimage_num; a++)
		kमुक्त(obj_handle->ae_uimage[a].page);

	क्रम (a = 0; a < handle->hal_handle->ae_max_num; a++)
		qat_uclo_मुक्त_ae_data(&obj_handle->ae_data[a]);

	kमुक्त(obj_handle->obj_hdr);
	kमुक्त(obj_handle->obj_buf);
	kमुक्त(obj_handle);
	handle->obj_handle = शून्य;
पूर्ण

अटल व्योम qat_uclo_fill_uwords(काष्ठा icp_qat_uclo_objhandle *obj_handle,
				 काष्ठा icp_qat_uclo_encap_page *encap_page,
				 u64 *uword, अचिन्हित पूर्णांक addr_p,
				 अचिन्हित पूर्णांक raddr, u64 fill)
अणु
	अचिन्हित पूर्णांक i, addr;
	u64 uwrd = 0;

	अगर (!encap_page) अणु
		*uword = fill;
		वापस;
	पूर्ण
	addr = (encap_page->page_region) ? raddr : addr_p;
	क्रम (i = 0; i < encap_page->uwblock_num; i++) अणु
		अगर (addr >= encap_page->uwblock[i].start_addr &&
		    addr <= encap_page->uwblock[i].start_addr +
		    encap_page->uwblock[i].words_num - 1) अणु
			addr -= encap_page->uwblock[i].start_addr;
			addr *= obj_handle->uword_in_bytes;
			स_नकल(&uwrd, (व्योम *)(((uपूर्णांकptr_t)
			       encap_page->uwblock[i].micro_words) + addr),
			       obj_handle->uword_in_bytes);
			uwrd = uwrd & GENMASK_ULL(43, 0);
		पूर्ण
	पूर्ण
	*uword = uwrd;
	अगर (*uword == INVLD_UWORD)
		*uword = fill;
पूर्ण

अटल व्योम qat_uclo_wr_uimage_raw_page(काष्ठा icp_qat_fw_loader_handle *handle,
					काष्ठा icp_qat_uclo_encap_page
					*encap_page, अचिन्हित पूर्णांक ae)
अणु
	अचिन्हित पूर्णांक uw_physical_addr, uw_relative_addr, i, words_num, cpylen;
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	u64 fill_pat;

	/* load the page starting at appropriate ustore address */
	/* get fill-pattern from an image -- they are all the same */
	स_नकल(&fill_pat, obj_handle->ae_uimage[0].img_ptr->fill_pattern,
	       माप(u64));
	uw_physical_addr = encap_page->beg_addr_p;
	uw_relative_addr = 0;
	words_num = encap_page->micro_words_num;
	जबतक (words_num) अणु
		अगर (words_num < UWORD_CPYBUF_SIZE)
			cpylen = words_num;
		अन्यथा
			cpylen = UWORD_CPYBUF_SIZE;

		/* load the buffer */
		क्रम (i = 0; i < cpylen; i++)
			qat_uclo_fill_uwords(obj_handle, encap_page,
					     &obj_handle->uword_buf[i],
					     uw_physical_addr + i,
					     uw_relative_addr + i, fill_pat);

		/* copy the buffer to ustore */
		qat_hal_wr_uwords(handle, (अचिन्हित अक्षर)ae,
				  uw_physical_addr, cpylen,
				  obj_handle->uword_buf);

		uw_physical_addr += cpylen;
		uw_relative_addr += cpylen;
		words_num -= cpylen;
	पूर्ण
पूर्ण

अटल व्योम qat_uclo_wr_uimage_page(काष्ठा icp_qat_fw_loader_handle *handle,
				    काष्ठा icp_qat_uof_image *image)
अणु
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित दीर्घ cfg_ae_mask = handle->cfg_ae_mask;
	अचिन्हित दीर्घ ae_asचिन्हित = image->ae_asचिन्हित;
	काष्ठा icp_qat_uclo_aedata *aed;
	अचिन्हित पूर्णांक ctx_mask, s;
	काष्ठा icp_qat_uclo_page *page;
	अचिन्हित अक्षर ae;
	पूर्णांक ctx;

	अगर (ICP_QAT_CTX_MODE(image->ae_mode) == ICP_QAT_UCLO_MAX_CTX)
		ctx_mask = 0xff;
	अन्यथा
		ctx_mask = 0x55;
	/* load the शेष page and set asचिन्हित CTX PC
	 * to the entrypoपूर्णांक address */
	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		अगर (!test_bit(ae, &cfg_ae_mask))
			जारी;

		अगर (!test_bit(ae, &ae_asचिन्हित))
			जारी;

		aed = &obj_handle->ae_data[ae];
		/* find the slice to which this image is asचिन्हित */
		क्रम (s = 0; s < aed->slice_num; s++) अणु
			अगर (image->ctx_asचिन्हित &
			    aed->ae_slices[s].ctx_mask_asचिन्हित)
				अवरोध;
		पूर्ण
		अगर (s >= aed->slice_num)
			जारी;
		page = aed->ae_slices[s].page;
		अगर (!page->encap_page->def_page)
			जारी;
		qat_uclo_wr_uimage_raw_page(handle, page->encap_page, ae);

		page = aed->ae_slices[s].page;
		क्रम (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++)
			aed->ae_slices[s].cur_page[ctx] =
					(ctx_mask & (1 << ctx)) ? page : शून्य;
		qat_hal_set_live_ctx(handle, (अचिन्हित अक्षर)ae,
				     image->ctx_asचिन्हित);
		qat_hal_set_pc(handle, (अचिन्हित अक्षर)ae, image->ctx_asचिन्हित,
			       image->entry_address);
	पूर्ण
पूर्ण

अटल पूर्णांक qat_uclo_wr_suof_img(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा icp_qat_fw_auth_desc *desc = शून्य;
	काष्ठा icp_qat_suof_handle *sobj_handle = handle->sobj_handle;
	काष्ठा icp_qat_suof_img_hdr *simg_hdr = sobj_handle->img_table.simg_hdr;

	क्रम (i = 0; i < sobj_handle->img_table.num_simgs; i++) अणु
		अगर (qat_uclo_map_auth_fw(handle,
					 (अक्षर *)simg_hdr[i].simg_buf,
					 (अचिन्हित पूर्णांक)
					 simg_hdr[i].simg_len,
					 &desc))
			जाओ wr_err;
		अगर (qat_uclo_auth_fw(handle, desc))
			जाओ wr_err;
		अगर (qat_uclo_is_broadcast(handle, i)) अणु
			अगर (qat_uclo_broadcast_load_fw(handle, desc))
				जाओ wr_err;
		पूर्ण अन्यथा अणु
			अगर (qat_uclo_load_fw(handle, desc))
				जाओ wr_err;
		पूर्ण
		qat_uclo_ummap_auth_fw(handle, &desc);
	पूर्ण
	वापस 0;
wr_err:
	qat_uclo_ummap_auth_fw(handle, &desc);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qat_uclo_wr_uof_img(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	काष्ठा icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	अचिन्हित पूर्णांक i;

	अगर (qat_uclo_init_globals(handle))
		वापस -EINVAL;
	क्रम (i = 0; i < obj_handle->uimage_num; i++) अणु
		अगर (!obj_handle->ae_uimage[i].img_ptr)
			वापस -EINVAL;
		अगर (qat_uclo_init_ustore(handle, &obj_handle->ae_uimage[i]))
			वापस -EINVAL;
		qat_uclo_wr_uimage_page(handle,
					obj_handle->ae_uimage[i].img_ptr);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qat_uclo_wr_all_uimage(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	वापस (handle->chip_info->fw_auth) ? qat_uclo_wr_suof_img(handle) :
				   qat_uclo_wr_uof_img(handle);
पूर्ण

पूर्णांक qat_uclo_set_cfg_ae_mask(काष्ठा icp_qat_fw_loader_handle *handle,
			     अचिन्हित पूर्णांक cfg_ae_mask)
अणु
	अगर (!cfg_ae_mask)
		वापस -EINVAL;

	handle->cfg_ae_mask = cfg_ae_mask;
	वापस 0;
पूर्ण
