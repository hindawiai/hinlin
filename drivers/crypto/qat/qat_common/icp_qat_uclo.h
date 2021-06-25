<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित __ICP_QAT_UCLO_H__
#घोषणा __ICP_QAT_UCLO_H__

#घोषणा ICP_QAT_AC_895XCC_DEV_TYPE 0x00400000
#घोषणा ICP_QAT_AC_C62X_DEV_TYPE   0x01000000
#घोषणा ICP_QAT_AC_C3XXX_DEV_TYPE  0x02000000
#घोषणा ICP_QAT_AC_4XXX_A_DEV_TYPE 0x08000000
#घोषणा ICP_QAT_UCLO_MAX_AE       12
#घोषणा ICP_QAT_UCLO_MAX_CTX      8
#घोषणा ICP_QAT_UCLO_MAX_UIMAGE   (ICP_QAT_UCLO_MAX_AE * ICP_QAT_UCLO_MAX_CTX)
#घोषणा ICP_QAT_UCLO_MAX_USTORE   0x4000
#घोषणा ICP_QAT_UCLO_MAX_XFER_REG 128
#घोषणा ICP_QAT_UCLO_MAX_GPR_REG  128
#घोषणा ICP_QAT_UCLO_MAX_LMEM_REG 1024
#घोषणा ICP_QAT_UCLO_MAX_LMEM_REG_2X 1280
#घोषणा ICP_QAT_UCLO_AE_ALL_CTX   0xff
#घोषणा ICP_QAT_UOF_OBJID_LEN     8
#घोषणा ICP_QAT_UOF_FID 0xc6c2
#घोषणा ICP_QAT_UOF_MAJVER 0x4
#घोषणा ICP_QAT_UOF_MINVER 0x11
#घोषणा ICP_QAT_UOF_OBJS        "UOF_OBJS"
#घोषणा ICP_QAT_UOF_STRT        "UOF_STRT"
#घोषणा ICP_QAT_UOF_IMAG        "UOF_IMAG"
#घोषणा ICP_QAT_UOF_IMEM        "UOF_IMEM"
#घोषणा ICP_QAT_UOF_LOCAL_SCOPE     1
#घोषणा ICP_QAT_UOF_INIT_EXPR               0
#घोषणा ICP_QAT_UOF_INIT_REG                1
#घोषणा ICP_QAT_UOF_INIT_REG_CTX            2
#घोषणा ICP_QAT_UOF_INIT_EXPR_ENDIAN_SWAP   3
#घोषणा ICP_QAT_SUOF_OBJ_ID_LEN             8
#घोषणा ICP_QAT_SUOF_FID  0x53554f46
#घोषणा ICP_QAT_SUOF_MAJVER 0x0
#घोषणा ICP_QAT_SUOF_MINVER 0x1
#घोषणा ICP_QAT_SUOF_OBJ_NAME_LEN 128
#घोषणा ICP_QAT_MOF_OBJ_ID_LEN 8
#घोषणा ICP_QAT_MOF_OBJ_CHUNKID_LEN 8
#घोषणा ICP_QAT_MOF_FID 0x00666f6d
#घोषणा ICP_QAT_MOF_MAJVER 0x0
#घोषणा ICP_QAT_MOF_MINVER 0x1
#घोषणा ICP_QAT_MOF_SYM_OBJS "SYM_OBJS"
#घोषणा ICP_QAT_SUOF_OBJS "SUF_OBJS"
#घोषणा ICP_QAT_SUOF_IMAG "SUF_IMAG"
#घोषणा ICP_QAT_SIMG_AE_INIT_SEQ_LEN    (50 * माप(अचिन्हित दीर्घ दीर्घ))
#घोषणा ICP_QAT_SIMG_AE_INSTS_LEN       (0x4000 * माप(अचिन्हित दीर्घ दीर्घ))

#घोषणा DSS_FWSK_MODULUS_LEN    384 /* RSA3K */
#घोषणा DSS_FWSK_EXPONENT_LEN   4
#घोषणा DSS_FWSK_PADDING_LEN    380
#घोषणा DSS_SIGNATURE_LEN       384 /* RSA3K */

#घोषणा CSS_FWSK_MODULUS_LEN    256 /* RSA2K */
#घोषणा CSS_FWSK_EXPONENT_LEN   4
#घोषणा CSS_FWSK_PADDING_LEN    252
#घोषणा CSS_SIGNATURE_LEN       256 /* RSA2K */

#घोषणा ICP_QAT_CSS_FWSK_MODULUS_LEN(handle)	((handle)->chip_info->css_3k ? \
						DSS_FWSK_MODULUS_LEN  : \
						CSS_FWSK_MODULUS_LEN)

#घोषणा ICP_QAT_CSS_FWSK_EXPONENT_LEN(handle)	((handle)->chip_info->css_3k ? \
						DSS_FWSK_EXPONENT_LEN : \
						CSS_FWSK_EXPONENT_LEN)

#घोषणा ICP_QAT_CSS_FWSK_PAD_LEN(handle)	((handle)->chip_info->css_3k ? \
						DSS_FWSK_PADDING_LEN : \
						CSS_FWSK_PADDING_LEN)

#घोषणा ICP_QAT_CSS_FWSK_PUB_LEN(handle)	(ICP_QAT_CSS_FWSK_MODULUS_LEN(handle) + \
						ICP_QAT_CSS_FWSK_EXPONENT_LEN(handle) + \
						ICP_QAT_CSS_FWSK_PAD_LEN(handle))

#घोषणा ICP_QAT_CSS_SIGNATURE_LEN(handle)	((handle)->chip_info->css_3k ? \
						DSS_SIGNATURE_LEN : \
						CSS_SIGNATURE_LEN)

#घोषणा ICP_QAT_CSS_AE_IMG_LEN     (माप(काष्ठा icp_qat_simg_ae_mode) + \
				    ICP_QAT_SIMG_AE_INIT_SEQ_LEN +         \
				    ICP_QAT_SIMG_AE_INSTS_LEN)
#घोषणा ICP_QAT_CSS_AE_SIMG_LEN(handle) (माप(काष्ठा icp_qat_css_hdr) + \
					ICP_QAT_CSS_FWSK_PUB_LEN(handle) + \
					ICP_QAT_CSS_SIGNATURE_LEN(handle) + \
					ICP_QAT_CSS_AE_IMG_LEN)
#घोषणा ICP_QAT_AE_IMG_OFFSET(handle) (माप(काष्ठा icp_qat_css_hdr) + \
					ICP_QAT_CSS_FWSK_MODULUS_LEN(handle) + \
					ICP_QAT_CSS_FWSK_EXPONENT_LEN(handle) + \
					ICP_QAT_CSS_SIGNATURE_LEN(handle))
#घोषणा ICP_QAT_CSS_MAX_IMAGE_LEN   0x40000

#घोषणा ICP_QAT_CTX_MODE(ae_mode) ((ae_mode) & 0xf)
#घोषणा ICP_QAT_NN_MODE(ae_mode) (((ae_mode) >> 0x4) & 0xf)
#घोषणा ICP_QAT_SHARED_USTORE_MODE(ae_mode) (((ae_mode) >> 0xb) & 0x1)
#घोषणा RELOADABLE_CTX_SHARED_MODE(ae_mode) (((ae_mode) >> 0xc) & 0x1)

#घोषणा ICP_QAT_LOC_MEM0_MODE(ae_mode) (((ae_mode) >> 0x8) & 0x1)
#घोषणा ICP_QAT_LOC_MEM1_MODE(ae_mode) (((ae_mode) >> 0x9) & 0x1)
#घोषणा ICP_QAT_LOC_MEM2_MODE(ae_mode) (((ae_mode) >> 0x6) & 0x1)
#घोषणा ICP_QAT_LOC_MEM3_MODE(ae_mode) (((ae_mode) >> 0x7) & 0x1)
#घोषणा ICP_QAT_LOC_TINDEX_MODE(ae_mode) (((ae_mode) >> 0xe) & 0x1)

क्रमागत icp_qat_uof_mem_region अणु
	ICP_QAT_UOF_SRAM_REGION = 0x0,
	ICP_QAT_UOF_LMEM_REGION = 0x3,
	ICP_QAT_UOF_UMEM_REGION = 0x5
पूर्ण;

क्रमागत icp_qat_uof_regtype अणु
	ICP_NO_DEST	= 0,
	ICP_GPA_REL	= 1,
	ICP_GPA_ABS	= 2,
	ICP_GPB_REL	= 3,
	ICP_GPB_ABS	= 4,
	ICP_SR_REL	= 5,
	ICP_SR_RD_REL	= 6,
	ICP_SR_WR_REL	= 7,
	ICP_SR_ABS	= 8,
	ICP_SR_RD_ABS	= 9,
	ICP_SR_WR_ABS	= 10,
	ICP_DR_REL	= 19,
	ICP_DR_RD_REL	= 20,
	ICP_DR_WR_REL	= 21,
	ICP_DR_ABS	= 22,
	ICP_DR_RD_ABS	= 23,
	ICP_DR_WR_ABS	= 24,
	ICP_LMEM	= 26,
	ICP_LMEM0	= 27,
	ICP_LMEM1	= 28,
	ICP_NEIGH_REL	= 31,
	ICP_LMEM2	= 61,
	ICP_LMEM3	= 62,
पूर्ण;

क्रमागत icp_qat_css_fwtype अणु
	CSS_AE_FIRMWARE = 0,
	CSS_MMP_FIRMWARE = 1
पूर्ण;

काष्ठा icp_qat_uclo_page अणु
	काष्ठा icp_qat_uclo_encap_page *encap_page;
	काष्ठा icp_qat_uclo_region *region;
	अचिन्हित पूर्णांक flags;
पूर्ण;

काष्ठा icp_qat_uclo_region अणु
	काष्ठा icp_qat_uclo_page *loaded;
	काष्ठा icp_qat_uclo_page *page;
पूर्ण;

काष्ठा icp_qat_uclo_aeslice अणु
	काष्ठा icp_qat_uclo_region *region;
	काष्ठा icp_qat_uclo_page *page;
	काष्ठा icp_qat_uclo_page *cur_page[ICP_QAT_UCLO_MAX_CTX];
	काष्ठा icp_qat_uclo_encapme *encap_image;
	अचिन्हित पूर्णांक ctx_mask_asचिन्हित;
	अचिन्हित पूर्णांक new_uaddr[ICP_QAT_UCLO_MAX_CTX];
पूर्ण;

काष्ठा icp_qat_uclo_aedata अणु
	अचिन्हित पूर्णांक slice_num;
	अचिन्हित पूर्णांक eff_ustore_size;
	काष्ठा icp_qat_uclo_aeslice ae_slices[ICP_QAT_UCLO_MAX_CTX];
पूर्ण;

काष्ठा icp_qat_uof_encap_obj अणु
	अक्षर *beg_uof;
	काष्ठा icp_qat_uof_objhdr *obj_hdr;
	काष्ठा icp_qat_uof_chunkhdr *chunk_hdr;
	काष्ठा icp_qat_uof_varmem_seg *var_mem_seg;
पूर्ण;

काष्ठा icp_qat_uclo_encap_uwblock अणु
	अचिन्हित पूर्णांक start_addr;
	अचिन्हित पूर्णांक words_num;
	u64 micro_words;
पूर्ण;

काष्ठा icp_qat_uclo_encap_page अणु
	अचिन्हित पूर्णांक def_page;
	अचिन्हित पूर्णांक page_region;
	अचिन्हित पूर्णांक beg_addr_v;
	अचिन्हित पूर्णांक beg_addr_p;
	अचिन्हित पूर्णांक micro_words_num;
	अचिन्हित पूर्णांक uwblock_num;
	काष्ठा icp_qat_uclo_encap_uwblock *uwblock;
पूर्ण;

काष्ठा icp_qat_uclo_encapme अणु
	काष्ठा icp_qat_uof_image *img_ptr;
	काष्ठा icp_qat_uclo_encap_page *page;
	अचिन्हित पूर्णांक ae_reg_num;
	काष्ठा icp_qat_uof_ae_reg *ae_reg;
	अचिन्हित पूर्णांक init_regsym_num;
	काष्ठा icp_qat_uof_init_regsym *init_regsym;
	अचिन्हित पूर्णांक sअवरोध_num;
	काष्ठा icp_qat_uof_sअवरोध *sअवरोध;
	अचिन्हित पूर्णांक uwords_num;
पूर्ण;

काष्ठा icp_qat_uclo_init_mem_table अणु
	अचिन्हित पूर्णांक entry_num;
	काष्ठा icp_qat_uof_iniपंचांगem *init_mem;
पूर्ण;

काष्ठा icp_qat_uclo_objhdr अणु
	अक्षर *file_buff;
	अचिन्हित पूर्णांक checksum;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा icp_qat_uof_strtable अणु
	अचिन्हित पूर्णांक table_len;
	अचिन्हित पूर्णांक reserved;
	u64 strings;
पूर्ण;

काष्ठा icp_qat_uclo_objhandle अणु
	अचिन्हित पूर्णांक prod_type;
	अचिन्हित पूर्णांक prod_rev;
	काष्ठा icp_qat_uclo_objhdr *obj_hdr;
	काष्ठा icp_qat_uof_encap_obj encap_uof_obj;
	काष्ठा icp_qat_uof_strtable str_table;
	काष्ठा icp_qat_uclo_encapme ae_uimage[ICP_QAT_UCLO_MAX_UIMAGE];
	काष्ठा icp_qat_uclo_aedata ae_data[ICP_QAT_UCLO_MAX_AE];
	काष्ठा icp_qat_uclo_init_mem_table init_mem_tab;
	काष्ठा icp_qat_uof_batch_init *lm_init_tab[ICP_QAT_UCLO_MAX_AE];
	काष्ठा icp_qat_uof_batch_init *umem_init_tab[ICP_QAT_UCLO_MAX_AE];
	पूर्णांक uimage_num;
	पूर्णांक uword_in_bytes;
	पूर्णांक global_inited;
	अचिन्हित पूर्णांक ae_num;
	अचिन्हित पूर्णांक ustore_phy_size;
	व्योम *obj_buf;
	u64 *uword_buf;
पूर्ण;

काष्ठा icp_qat_uof_uword_block अणु
	अचिन्हित पूर्णांक start_addr;
	अचिन्हित पूर्णांक words_num;
	अचिन्हित पूर्णांक uword_offset;
	अचिन्हित पूर्णांक reserved;
पूर्ण;

काष्ठा icp_qat_uof_filehdr अणु
	अचिन्हित लघु file_id;
	अचिन्हित लघु reserved1;
	अक्षर min_ver;
	अक्षर maj_ver;
	अचिन्हित लघु reserved2;
	अचिन्हित लघु max_chunks;
	अचिन्हित लघु num_chunks;
पूर्ण;

काष्ठा icp_qat_uof_filechunkhdr अणु
	अक्षर chunk_id[ICP_QAT_UOF_OBJID_LEN];
	अचिन्हित पूर्णांक checksum;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा icp_qat_uof_objhdr अणु
	अचिन्हित पूर्णांक ac_dev_type;
	अचिन्हित लघु min_cpu_ver;
	अचिन्हित लघु max_cpu_ver;
	लघु max_chunks;
	लघु num_chunks;
	अचिन्हित पूर्णांक reserved1;
	अचिन्हित पूर्णांक reserved2;
पूर्ण;

काष्ठा icp_qat_uof_chunkhdr अणु
	अक्षर chunk_id[ICP_QAT_UOF_OBJID_LEN];
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा icp_qat_uof_memvar_attr अणु
	अचिन्हित पूर्णांक offset_in_byte;
	अचिन्हित पूर्णांक value;
पूर्ण;

काष्ठा icp_qat_uof_iniपंचांगem अणु
	अचिन्हित पूर्णांक sym_name;
	अक्षर region;
	अक्षर scope;
	अचिन्हित लघु reserved1;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक num_in_bytes;
	अचिन्हित पूर्णांक val_attr_num;
पूर्ण;

काष्ठा icp_qat_uof_init_regsym अणु
	अचिन्हित पूर्णांक sym_name;
	अक्षर init_type;
	अक्षर value_type;
	अक्षर reg_type;
	अचिन्हित अक्षर ctx;
	अचिन्हित पूर्णांक reg_addr;
	अचिन्हित पूर्णांक value;
पूर्ण;

काष्ठा icp_qat_uof_varmem_seg अणु
	अचिन्हित पूर्णांक sram_base;
	अचिन्हित पूर्णांक sram_size;
	अचिन्हित पूर्णांक sram_alignment;
	अचिन्हित पूर्णांक sdram_base;
	अचिन्हित पूर्णांक sdram_size;
	अचिन्हित पूर्णांक sdram_alignment;
	अचिन्हित पूर्णांक sdram1_base;
	अचिन्हित पूर्णांक sdram1_size;
	अचिन्हित पूर्णांक sdram1_alignment;
	अचिन्हित पूर्णांक scratch_base;
	अचिन्हित पूर्णांक scratch_size;
	अचिन्हित पूर्णांक scratch_alignment;
पूर्ण;

काष्ठा icp_qat_uof_gtid अणु
	अक्षर tool_id[ICP_QAT_UOF_OBJID_LEN];
	पूर्णांक tool_ver;
	अचिन्हित पूर्णांक reserved1;
	अचिन्हित पूर्णांक reserved2;
पूर्ण;

काष्ठा icp_qat_uof_sअवरोध अणु
	अचिन्हित पूर्णांक page_num;
	अचिन्हित पूर्णांक virt_uaddr;
	अचिन्हित अक्षर sअवरोध_type;
	अचिन्हित अक्षर reg_type;
	अचिन्हित लघु reserved1;
	अचिन्हित पूर्णांक addr_offset;
	अचिन्हित पूर्णांक reg_addr;
पूर्ण;

काष्ठा icp_qat_uof_code_page अणु
	अचिन्हित पूर्णांक page_region;
	अचिन्हित पूर्णांक page_num;
	अचिन्हित अक्षर def_page;
	अचिन्हित अक्षर reserved2;
	अचिन्हित लघु reserved1;
	अचिन्हित पूर्णांक beg_addr_v;
	अचिन्हित पूर्णांक beg_addr_p;
	अचिन्हित पूर्णांक neigh_reg_tab_offset;
	अचिन्हित पूर्णांक uc_var_tab_offset;
	अचिन्हित पूर्णांक imp_var_tab_offset;
	अचिन्हित पूर्णांक imp_expr_tab_offset;
	अचिन्हित पूर्णांक code_area_offset;
पूर्ण;

काष्ठा icp_qat_uof_image अणु
	अचिन्हित पूर्णांक img_name;
	अचिन्हित पूर्णांक ae_asचिन्हित;
	अचिन्हित पूर्णांक ctx_asचिन्हित;
	अचिन्हित पूर्णांक ac_dev_type;
	अचिन्हित पूर्णांक entry_address;
	अचिन्हित पूर्णांक fill_pattern[2];
	अचिन्हित पूर्णांक reloadable_size;
	अचिन्हित अक्षर sensitivity;
	अचिन्हित अक्षर reserved;
	अचिन्हित लघु ae_mode;
	अचिन्हित लघु max_ver;
	अचिन्हित लघु min_ver;
	अचिन्हित लघु image_attrib;
	अचिन्हित लघु reserved2;
	अचिन्हित लघु page_region_num;
	अचिन्हित लघु numpages;
	अचिन्हित पूर्णांक reg_tab_offset;
	अचिन्हित पूर्णांक init_reg_sym_tab;
	अचिन्हित पूर्णांक sअवरोध_tab;
	अचिन्हित पूर्णांक app_metadata;
पूर्ण;

काष्ठा icp_qat_uof_objtable अणु
	अचिन्हित पूर्णांक entry_num;
पूर्ण;

काष्ठा icp_qat_uof_ae_reg अणु
	अचिन्हित पूर्णांक name;
	अचिन्हित पूर्णांक vis_name;
	अचिन्हित लघु type;
	अचिन्हित लघु addr;
	अचिन्हित लघु access_mode;
	अचिन्हित अक्षर visible;
	अचिन्हित अक्षर reserved1;
	अचिन्हित लघु ref_count;
	अचिन्हित लघु reserved2;
	अचिन्हित पूर्णांक xo_id;
पूर्ण;

काष्ठा icp_qat_uof_code_area अणु
	अचिन्हित पूर्णांक micro_words_num;
	अचिन्हित पूर्णांक uword_block_tab;
पूर्ण;

काष्ठा icp_qat_uof_batch_init अणु
	अचिन्हित पूर्णांक ae;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक *value;
	अचिन्हित पूर्णांक size;
	काष्ठा icp_qat_uof_batch_init *next;
पूर्ण;

काष्ठा icp_qat_suof_img_hdr अणु
	अक्षर          *simg_buf;
	अचिन्हित दीर्घ simg_len;
	अक्षर          *css_header;
	अक्षर          *css_key;
	अक्षर          *css_signature;
	अक्षर          *css_simg;
	अचिन्हित दीर्घ simg_size;
	अचिन्हित पूर्णांक  ae_num;
	अचिन्हित पूर्णांक  ae_mask;
	अचिन्हित पूर्णांक  fw_type;
	अचिन्हित दीर्घ simg_name;
	अचिन्हित दीर्घ appmeta_data;
पूर्ण;

काष्ठा icp_qat_suof_img_tbl अणु
	अचिन्हित पूर्णांक num_simgs;
	काष्ठा icp_qat_suof_img_hdr *simg_hdr;
पूर्ण;

काष्ठा icp_qat_suof_handle अणु
	अचिन्हित पूर्णांक  file_id;
	अचिन्हित पूर्णांक  check_sum;
	अक्षर          min_ver;
	अक्षर          maj_ver;
	अक्षर          fw_type;
	अक्षर          *suof_buf;
	अचिन्हित पूर्णांक  suof_size;
	अक्षर          *sym_str;
	अचिन्हित पूर्णांक  sym_size;
	काष्ठा icp_qat_suof_img_tbl img_table;
पूर्ण;

काष्ठा icp_qat_fw_auth_desc अणु
	अचिन्हित पूर्णांक   img_len;
	अचिन्हित पूर्णांक   ae_mask;
	अचिन्हित पूर्णांक   css_hdr_high;
	अचिन्हित पूर्णांक   css_hdr_low;
	अचिन्हित पूर्णांक   img_high;
	अचिन्हित पूर्णांक   img_low;
	अचिन्हित पूर्णांक   signature_high;
	अचिन्हित पूर्णांक   signature_low;
	अचिन्हित पूर्णांक   fwsk_pub_high;
	अचिन्हित पूर्णांक   fwsk_pub_low;
	अचिन्हित पूर्णांक   img_ae_mode_data_high;
	अचिन्हित पूर्णांक   img_ae_mode_data_low;
	अचिन्हित पूर्णांक   img_ae_init_data_high;
	अचिन्हित पूर्णांक   img_ae_init_data_low;
	अचिन्हित पूर्णांक   img_ae_insts_high;
	अचिन्हित पूर्णांक   img_ae_insts_low;
पूर्ण;

काष्ठा icp_qat_auth_chunk अणु
	काष्ठा icp_qat_fw_auth_desc fw_auth_desc;
	u64 chunk_size;
	u64 chunk_bus_addr;
पूर्ण;

काष्ठा icp_qat_css_hdr अणु
	अचिन्हित पूर्णांक module_type;
	अचिन्हित पूर्णांक header_len;
	अचिन्हित पूर्णांक header_ver;
	अचिन्हित पूर्णांक module_id;
	अचिन्हित पूर्णांक module_venकरोr;
	अचिन्हित पूर्णांक date;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक key_size;
	अचिन्हित पूर्णांक module_size;
	अचिन्हित पूर्णांक exponent_size;
	अचिन्हित पूर्णांक fw_type;
	अचिन्हित पूर्णांक reserved[21];
पूर्ण;

काष्ठा icp_qat_simg_ae_mode अणु
	अचिन्हित पूर्णांक     file_id;
	अचिन्हित लघु   maj_ver;
	अचिन्हित लघु   min_ver;
	अचिन्हित पूर्णांक     dev_type;
	अचिन्हित लघु   devmax_ver;
	अचिन्हित लघु   devmin_ver;
	अचिन्हित पूर्णांक     ae_mask;
	अचिन्हित पूर्णांक     ctx_enables;
	अक्षर             fw_type;
	अक्षर             ctx_mode;
	अक्षर             nn_mode;
	अक्षर             lm0_mode;
	अक्षर             lm1_mode;
	अक्षर             scs_mode;
	अक्षर             lm2_mode;
	अक्षर             lm3_mode;
	अक्षर             tindex_mode;
	अचिन्हित अक्षर    reserved[7];
	अक्षर             simg_name[256];
	अक्षर             appmeta_data[256];
पूर्ण;

काष्ठा icp_qat_suof_filehdr अणु
	अचिन्हित पूर्णांक     file_id;
	अचिन्हित पूर्णांक     check_sum;
	अक्षर             min_ver;
	अक्षर             maj_ver;
	अक्षर             fw_type;
	अक्षर             reserved;
	अचिन्हित लघु   max_chunks;
	अचिन्हित लघु   num_chunks;
पूर्ण;

काष्ठा icp_qat_suof_chunk_hdr अणु
	अक्षर chunk_id[ICP_QAT_SUOF_OBJ_ID_LEN];
	u64 offset;
	u64 size;
पूर्ण;

काष्ठा icp_qat_suof_strtable अणु
	अचिन्हित पूर्णांक tab_length;
	अचिन्हित पूर्णांक strings;
पूर्ण;

काष्ठा icp_qat_suof_objhdr अणु
	अचिन्हित पूर्णांक img_length;
	अचिन्हित पूर्णांक reserved;
पूर्ण;

काष्ठा icp_qat_mof_file_hdr अणु
	अचिन्हित पूर्णांक file_id;
	अचिन्हित पूर्णांक checksum;
	अक्षर min_ver;
	अक्षर maj_ver;
	अचिन्हित लघु reserved;
	अचिन्हित लघु max_chunks;
	अचिन्हित लघु num_chunks;
पूर्ण;

काष्ठा icp_qat_mof_chunkhdr अणु
	अक्षर chunk_id[ICP_QAT_MOF_OBJ_ID_LEN];
	u64 offset;
	u64 size;
पूर्ण;

काष्ठा icp_qat_mof_str_table अणु
	अचिन्हित पूर्णांक tab_len;
	अचिन्हित पूर्णांक strings;
पूर्ण;

काष्ठा icp_qat_mof_obj_hdr अणु
	अचिन्हित लघु max_chunks;
	अचिन्हित लघु num_chunks;
	अचिन्हित पूर्णांक reserved;
पूर्ण;

काष्ठा icp_qat_mof_obj_chunkhdr अणु
	अक्षर chunk_id[ICP_QAT_MOF_OBJ_CHUNKID_LEN];
	u64 offset;
	u64 size;
	अचिन्हित पूर्णांक name;
	अचिन्हित पूर्णांक reserved;
पूर्ण;

काष्ठा icp_qat_mof_objhdr अणु
	अक्षर *obj_name;
	अक्षर *obj_buf;
	अचिन्हित पूर्णांक obj_size;
पूर्ण;

काष्ठा icp_qat_mof_table अणु
	अचिन्हित पूर्णांक num_objs;
	काष्ठा icp_qat_mof_objhdr *obj_hdr;
पूर्ण;

काष्ठा icp_qat_mof_handle अणु
	अचिन्हित पूर्णांक file_id;
	अचिन्हित पूर्णांक checksum;
	अक्षर min_ver;
	अक्षर maj_ver;
	अक्षर *mof_buf;
	u32 mof_size;
	अक्षर *sym_str;
	अचिन्हित पूर्णांक sym_size;
	अक्षर *uobjs_hdr;
	अक्षर *sobjs_hdr;
	काष्ठा icp_qat_mof_table obj_table;
पूर्ण;
#पूर्ण_अगर
