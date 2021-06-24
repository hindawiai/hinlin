<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/ethtool.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "nfp_asm.h"
#समावेश "nfp_main.h"
#समावेश "nfpcore/nfp.h"
#समावेश "nfpcore/nfp_nffw.h"
#समावेश "nfpcore/nfp6000/nfp6000.h"

#घोषणा NFP_DUMP_SPEC_RTSYM	"_abi_dump_spec"

#घोषणा ALIGN8(x)	ALIGN(x, 8)

क्रमागत nfp_dumpspec_type अणु
	NFP_DUMPSPEC_TYPE_CPP_CSR = 0,
	NFP_DUMPSPEC_TYPE_XPB_CSR = 1,
	NFP_DUMPSPEC_TYPE_ME_CSR = 2,
	NFP_DUMPSPEC_TYPE_INसूचीECT_ME_CSR = 3,
	NFP_DUMPSPEC_TYPE_RTSYM = 4,
	NFP_DUMPSPEC_TYPE_HWINFO = 5,
	NFP_DUMPSPEC_TYPE_FWNAME = 6,
	NFP_DUMPSPEC_TYPE_HWINFO_FIELD = 7,
	NFP_DUMPSPEC_TYPE_PROLOG = 10000,
	NFP_DUMPSPEC_TYPE_ERROR = 10001,
पूर्ण;

/* The following काष्ठाs must be carefully aligned so that they can be used to
 * पूर्णांकerpret the binary dumpspec and populate the dump data in a deterministic
 * way.
 */

/* generic type plus length */
काष्ठा nfp_dump_tl अणु
	__be32 type;
	__be32 length;	/* chunk length to follow, aligned to 8 bytes */
	अक्षर data[];
पूर्ण;

/* NFP CPP parameters */
काष्ठा nfp_dumpspec_cpp_isl_id अणु
	u8 target;
	u8 action;
	u8 token;
	u8 island;
पूर्ण;

काष्ठा nfp_dump_common_cpp अणु
	काष्ठा nfp_dumpspec_cpp_isl_id cpp_id;
	__be32 offset;		/* address to start dump */
	__be32 dump_length;	/* total bytes to dump, aligned to reg size */
पूर्ण;

/* CSR dumpables */
काष्ठा nfp_dumpspec_csr अणु
	काष्ठा nfp_dump_tl tl;
	काष्ठा nfp_dump_common_cpp cpp;
	__be32 रेजिस्टर_width;	/* in bits */
पूर्ण;

काष्ठा nfp_dumpspec_rtsym अणु
	काष्ठा nfp_dump_tl tl;
	अक्षर rtsym[];
पूर्ण;

/* header क्रम रेजिस्टर dumpable */
काष्ठा nfp_dump_csr अणु
	काष्ठा nfp_dump_tl tl;
	काष्ठा nfp_dump_common_cpp cpp;
	__be32 रेजिस्टर_width;	/* in bits */
	__be32 error;		/* error code encountered जबतक पढ़ोing */
	__be32 error_offset;	/* offset being पढ़ो when error occurred */
पूर्ण;

काष्ठा nfp_dump_rtsym अणु
	काष्ठा nfp_dump_tl tl;
	काष्ठा nfp_dump_common_cpp cpp;
	__be32 error;		/* error code encountered जबतक पढ़ोing */
	u8 padded_name_length;	/* pad so data starts at 8 byte boundary */
	अक्षर rtsym[];
	/* after padded_name_length, there is dump_length data */
पूर्ण;

काष्ठा nfp_dump_prolog अणु
	काष्ठा nfp_dump_tl tl;
	__be32 dump_level;
पूर्ण;

काष्ठा nfp_dump_error अणु
	काष्ठा nfp_dump_tl tl;
	__be32 error;
	अक्षर padding[4];
	अक्षर spec[];
पूर्ण;

/* to track state through debug size calculation TLV traversal */
काष्ठा nfp_level_size अणु
	__be32 requested_level;	/* input */
	u32 total_size;		/* output */
पूर्ण;

/* to track state during debug dump creation TLV traversal */
काष्ठा nfp_dump_state अणु
	__be32 requested_level;	/* input param */
	u32 dumped_size;	/* adds up to size of dumped data */
	u32 buf_size;		/* size of buffer poपूर्णांकer to by p */
	व्योम *p;		/* current poपूर्णांक in dump buffer */
पूर्ण;

प्रकार पूर्णांक (*nfp_tlv_visit)(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_tl *tl,
			     व्योम *param);

अटल पूर्णांक
nfp_traverse_tlvs(काष्ठा nfp_pf *pf, व्योम *data, u32 data_length, व्योम *param,
		  nfp_tlv_visit tlv_visit)
अणु
	दीर्घ दीर्घ reमुख्यing = data_length;
	काष्ठा nfp_dump_tl *tl;
	u32 total_tlv_size;
	व्योम *p = data;
	पूर्णांक err;

	जबतक (reमुख्यing >= माप(*tl)) अणु
		tl = p;
		अगर (!tl->type && !tl->length)
			अवरोध;

		अगर (be32_to_cpu(tl->length) > reमुख्यing - माप(*tl))
			वापस -EINVAL;

		total_tlv_size = माप(*tl) + be32_to_cpu(tl->length);

		/* Spec TLVs should be aligned to 4 bytes. */
		अगर (total_tlv_size % 4 != 0)
			वापस -EINVAL;

		p += total_tlv_size;
		reमुख्यing -= total_tlv_size;
		err = tlv_visit(pf, tl, param);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 nfp_get_numeric_cpp_id(काष्ठा nfp_dumpspec_cpp_isl_id *cpp_id)
अणु
	वापस NFP_CPP_ISLAND_ID(cpp_id->target, cpp_id->action, cpp_id->token,
				 cpp_id->island);
पूर्ण

काष्ठा nfp_dumpspec *
nfp_net_dump_load_dumpspec(काष्ठा nfp_cpp *cpp, काष्ठा nfp_rtsym_table *rtbl)
अणु
	स्थिर काष्ठा nfp_rtsym *specsym;
	काष्ठा nfp_dumpspec *dumpspec;
	पूर्णांक bytes_पढ़ो;
	u64 sym_size;

	specsym = nfp_rtsym_lookup(rtbl, NFP_DUMP_SPEC_RTSYM);
	अगर (!specsym)
		वापस शून्य;
	sym_size = nfp_rtsym_size(specsym);

	/* expected size of this buffer is in the order of tens of kilobytes */
	dumpspec = vदो_स्मृति(माप(*dumpspec) + sym_size);
	अगर (!dumpspec)
		वापस शून्य;
	dumpspec->size = sym_size;

	bytes_पढ़ो = nfp_rtsym_पढ़ो(cpp, specsym, 0, dumpspec->data, sym_size);
	अगर (bytes_पढ़ो != sym_size) अणु
		vमुक्त(dumpspec);
		nfp_warn(cpp, "Debug dump specification read failed.\n");
		वापस शून्य;
	पूर्ण

	वापस dumpspec;
पूर्ण

अटल पूर्णांक nfp_dump_error_tlv_size(काष्ठा nfp_dump_tl *spec)
अणु
	वापस ALIGN8(माप(काष्ठा nfp_dump_error) + माप(*spec) +
		      be32_to_cpu(spec->length));
पूर्ण

अटल पूर्णांक nfp_calc_fwname_tlv_size(काष्ठा nfp_pf *pf)
अणु
	u32 fwname_len = म_माप(nfp_mip_name(pf->mip));

	वापस माप(काष्ठा nfp_dump_tl) + ALIGN8(fwname_len + 1);
पूर्ण

अटल पूर्णांक nfp_calc_hwinfo_field_sz(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_tl *spec)
अणु
	u32 tl_len, key_len;
	स्थिर अक्षर *value;

	tl_len = be32_to_cpu(spec->length);
	key_len = strnlen(spec->data, tl_len);
	अगर (key_len == tl_len)
		वापस nfp_dump_error_tlv_size(spec);

	value = nfp_hwinfo_lookup(pf->hwinfo, spec->data);
	अगर (!value)
		वापस nfp_dump_error_tlv_size(spec);

	वापस माप(काष्ठा nfp_dump_tl) + ALIGN8(key_len + म_माप(value) + 2);
पूर्ण

अटल bool nfp_csr_spec_valid(काष्ठा nfp_dumpspec_csr *spec_csr)
अणु
	u32 required_पढ़ो_sz = माप(*spec_csr) - माप(spec_csr->tl);
	u32 available_sz = be32_to_cpu(spec_csr->tl.length);
	u32 reg_width;

	अगर (available_sz < required_पढ़ो_sz)
		वापस false;

	reg_width = be32_to_cpu(spec_csr->रेजिस्टर_width);

	वापस reg_width == 32 || reg_width == 64;
पूर्ण

अटल पूर्णांक
nfp_calc_rtsym_dump_sz(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_tl *spec)
अणु
	काष्ठा nfp_rtsym_table *rtbl = pf->rtbl;
	काष्ठा nfp_dumpspec_rtsym *spec_rtsym;
	स्थिर काष्ठा nfp_rtsym *sym;
	u32 tl_len, key_len;

	spec_rtsym = (काष्ठा nfp_dumpspec_rtsym *)spec;
	tl_len = be32_to_cpu(spec->length);
	key_len = strnlen(spec_rtsym->rtsym, tl_len);
	अगर (key_len == tl_len)
		वापस nfp_dump_error_tlv_size(spec);

	sym = nfp_rtsym_lookup(rtbl, spec_rtsym->rtsym);
	अगर (!sym)
		वापस nfp_dump_error_tlv_size(spec);

	वापस ALIGN8(दुरत्व(काष्ठा nfp_dump_rtsym, rtsym) + key_len + 1) +
	       ALIGN8(nfp_rtsym_size(sym));
पूर्ण

अटल पूर्णांक
nfp_add_tlv_size(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_tl *tl, व्योम *param)
अणु
	काष्ठा nfp_dumpspec_csr *spec_csr;
	u32 *size = param;
	u32 hwinfo_size;

	चयन (be32_to_cpu(tl->type)) अणु
	हाल NFP_DUMPSPEC_TYPE_FWNAME:
		*size += nfp_calc_fwname_tlv_size(pf);
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_CPP_CSR:
	हाल NFP_DUMPSPEC_TYPE_XPB_CSR:
	हाल NFP_DUMPSPEC_TYPE_ME_CSR:
		spec_csr = (काष्ठा nfp_dumpspec_csr *)tl;
		अगर (!nfp_csr_spec_valid(spec_csr))
			*size += nfp_dump_error_tlv_size(tl);
		अन्यथा
			*size += ALIGN8(माप(काष्ठा nfp_dump_csr)) +
				 ALIGN8(be32_to_cpu(spec_csr->cpp.dump_length));
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_INसूचीECT_ME_CSR:
		spec_csr = (काष्ठा nfp_dumpspec_csr *)tl;
		अगर (!nfp_csr_spec_valid(spec_csr))
			*size += nfp_dump_error_tlv_size(tl);
		अन्यथा
			*size += ALIGN8(माप(काष्ठा nfp_dump_csr)) +
				 ALIGN8(be32_to_cpu(spec_csr->cpp.dump_length) *
					NFP_IND_NUM_CONTEXTS);
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_RTSYM:
		*size += nfp_calc_rtsym_dump_sz(pf, tl);
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_HWINFO:
		hwinfo_size = nfp_hwinfo_get_packed_str_size(pf->hwinfo);
		*size += माप(काष्ठा nfp_dump_tl) + ALIGN8(hwinfo_size);
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_HWINFO_FIELD:
		*size += nfp_calc_hwinfo_field_sz(pf, tl);
		अवरोध;
	शेष:
		*size += nfp_dump_error_tlv_size(tl);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_calc_specअगरic_level_size(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_tl *dump_level,
			     व्योम *param)
अणु
	काष्ठा nfp_level_size *lev_sz = param;

	अगर (dump_level->type != lev_sz->requested_level)
		वापस 0;

	वापस nfp_traverse_tlvs(pf, dump_level->data,
				 be32_to_cpu(dump_level->length),
				 &lev_sz->total_size, nfp_add_tlv_size);
पूर्ण

s64 nfp_net_dump_calculate_size(काष्ठा nfp_pf *pf, काष्ठा nfp_dumpspec *spec,
				u32 flag)
अणु
	काष्ठा nfp_level_size lev_sz;
	पूर्णांक err;

	lev_sz.requested_level = cpu_to_be32(flag);
	lev_sz.total_size = ALIGN8(माप(काष्ठा nfp_dump_prolog));

	err = nfp_traverse_tlvs(pf, spec->data, spec->size, &lev_sz,
				nfp_calc_specअगरic_level_size);
	अगर (err)
		वापस err;

	वापस lev_sz.total_size;
पूर्ण

अटल पूर्णांक nfp_add_tlv(u32 type, u32 total_tlv_sz, काष्ठा nfp_dump_state *dump)
अणु
	काष्ठा nfp_dump_tl *tl = dump->p;

	अगर (total_tlv_sz > dump->buf_size)
		वापस -ENOSPC;

	अगर (dump->buf_size - total_tlv_sz < dump->dumped_size)
		वापस -ENOSPC;

	tl->type = cpu_to_be32(type);
	tl->length = cpu_to_be32(total_tlv_sz - माप(*tl));

	dump->dumped_size += total_tlv_sz;
	dump->p += total_tlv_sz;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_dump_error_tlv(काष्ठा nfp_dump_tl *spec, पूर्णांक error,
		   काष्ठा nfp_dump_state *dump)
अणु
	काष्ठा nfp_dump_error *dump_header = dump->p;
	u32 total_spec_size, total_size;
	पूर्णांक err;

	total_spec_size = माप(*spec) + be32_to_cpu(spec->length);
	total_size = ALIGN8(माप(*dump_header) + total_spec_size);

	err = nfp_add_tlv(NFP_DUMPSPEC_TYPE_ERROR, total_size, dump);
	अगर (err)
		वापस err;

	dump_header->error = cpu_to_be32(error);
	स_नकल(dump_header->spec, spec, total_spec_size);

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_dump_fwname(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_state *dump)
अणु
	काष्ठा nfp_dump_tl *dump_header = dump->p;
	u32 fwname_len, total_size;
	स्थिर अक्षर *fwname;
	पूर्णांक err;

	fwname = nfp_mip_name(pf->mip);
	fwname_len = म_माप(fwname);
	total_size = माप(*dump_header) + ALIGN8(fwname_len + 1);

	err = nfp_add_tlv(NFP_DUMPSPEC_TYPE_FWNAME, total_size, dump);
	अगर (err)
		वापस err;

	स_नकल(dump_header->data, fwname, fwname_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_dump_hwinfo(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_tl *spec,
		काष्ठा nfp_dump_state *dump)
अणु
	काष्ठा nfp_dump_tl *dump_header = dump->p;
	u32 hwinfo_size, total_size;
	अक्षर *hwinfo;
	पूर्णांक err;

	hwinfo = nfp_hwinfo_get_packed_strings(pf->hwinfo);
	hwinfo_size = nfp_hwinfo_get_packed_str_size(pf->hwinfo);
	total_size = माप(*dump_header) + ALIGN8(hwinfo_size);

	err = nfp_add_tlv(NFP_DUMPSPEC_TYPE_HWINFO, total_size, dump);
	अगर (err)
		वापस err;

	स_नकल(dump_header->data, hwinfo, hwinfo_size);

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_dump_hwinfo_field(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_tl *spec,
				 काष्ठा nfp_dump_state *dump)
अणु
	काष्ठा nfp_dump_tl *dump_header = dump->p;
	u32 tl_len, key_len, val_len;
	स्थिर अक्षर *key, *value;
	u32 total_size;
	पूर्णांक err;

	tl_len = be32_to_cpu(spec->length);
	key_len = strnlen(spec->data, tl_len);
	अगर (key_len == tl_len)
		वापस nfp_dump_error_tlv(spec, -EINVAL, dump);

	key = spec->data;
	value = nfp_hwinfo_lookup(pf->hwinfo, key);
	अगर (!value)
		वापस nfp_dump_error_tlv(spec, -ENOENT, dump);

	val_len = म_माप(value);
	total_size = माप(*dump_header) + ALIGN8(key_len + val_len + 2);
	err = nfp_add_tlv(NFP_DUMPSPEC_TYPE_HWINFO_FIELD, total_size, dump);
	अगर (err)
		वापस err;

	स_नकल(dump_header->data, key, key_len + 1);
	स_नकल(dump_header->data + key_len + 1, value, val_len + 1);

	वापस 0;
पूर्ण

अटल bool is_xpb_पढ़ो(काष्ठा nfp_dumpspec_cpp_isl_id *cpp_id)
अणु
	वापस cpp_id->target == NFP_CPP_TARGET_ISLAND_XPB &&
	       cpp_id->action == 0 && cpp_id->token == 0;
पूर्ण

अटल पूर्णांक
nfp_dump_csr_range(काष्ठा nfp_pf *pf, काष्ठा nfp_dumpspec_csr *spec_csr,
		   काष्ठा nfp_dump_state *dump)
अणु
	काष्ठा nfp_dump_csr *dump_header = dump->p;
	u32 reg_sz, header_size, total_size;
	u32 cpp_rd_addr, max_rd_addr;
	पूर्णांक bytes_पढ़ो;
	व्योम *dest;
	u32 cpp_id;
	पूर्णांक err;

	अगर (!nfp_csr_spec_valid(spec_csr))
		वापस nfp_dump_error_tlv(&spec_csr->tl, -EINVAL, dump);

	reg_sz = be32_to_cpu(spec_csr->रेजिस्टर_width) / BITS_PER_BYTE;
	header_size = ALIGN8(माप(*dump_header));
	total_size = header_size +
		     ALIGN8(be32_to_cpu(spec_csr->cpp.dump_length));
	dest = dump->p + header_size;

	err = nfp_add_tlv(be32_to_cpu(spec_csr->tl.type), total_size, dump);
	अगर (err)
		वापस err;

	dump_header->cpp = spec_csr->cpp;
	dump_header->रेजिस्टर_width = spec_csr->रेजिस्टर_width;

	cpp_id = nfp_get_numeric_cpp_id(&spec_csr->cpp.cpp_id);
	cpp_rd_addr = be32_to_cpu(spec_csr->cpp.offset);
	max_rd_addr = cpp_rd_addr + be32_to_cpu(spec_csr->cpp.dump_length);

	जबतक (cpp_rd_addr < max_rd_addr) अणु
		अगर (is_xpb_पढ़ो(&spec_csr->cpp.cpp_id)) अणु
			err = nfp_xpb_पढ़ोl(pf->cpp, cpp_rd_addr, (u32 *)dest);
		पूर्ण अन्यथा अणु
			bytes_पढ़ो = nfp_cpp_पढ़ो(pf->cpp, cpp_id, cpp_rd_addr,
						  dest, reg_sz);
			err = bytes_पढ़ो == reg_sz ? 0 : -EIO;
		पूर्ण
		अगर (err) अणु
			dump_header->error = cpu_to_be32(err);
			dump_header->error_offset = cpu_to_be32(cpp_rd_addr);
			अवरोध;
		पूर्ण
		cpp_rd_addr += reg_sz;
		dest += reg_sz;
	पूर्ण

	वापस 0;
पूर्ण

/* Write context to CSRCtxPtr, then पढ़ो from it. Then the value can be पढ़ो
 * from IndCtxStatus.
 */
अटल पूर्णांक
nfp_पढ़ो_indirect_csr(काष्ठा nfp_cpp *cpp,
		      काष्ठा nfp_dumpspec_cpp_isl_id cpp_params, u32 offset,
		      u32 reg_sz, u32 context, व्योम *dest)
अणु
	u32 csr_ctx_ptr_offs;
	u32 cpp_id;
	पूर्णांक result;

	csr_ctx_ptr_offs = nfp_get_ind_csr_ctx_ptr_offs(offset);
	cpp_id = NFP_CPP_ISLAND_ID(cpp_params.target,
				   NFP_IND_ME_REFL_WR_SIG_INIT,
				   cpp_params.token, cpp_params.island);
	result = nfp_cpp_ग_लिखोl(cpp, cpp_id, csr_ctx_ptr_offs, context);
	अगर (result)
		वापस result;

	cpp_id = nfp_get_numeric_cpp_id(&cpp_params);
	result = nfp_cpp_पढ़ो(cpp, cpp_id, csr_ctx_ptr_offs, dest, reg_sz);
	अगर (result != reg_sz)
		वापस result < 0 ? result : -EIO;

	result = nfp_cpp_पढ़ो(cpp, cpp_id, offset, dest, reg_sz);
	अगर (result != reg_sz)
		वापस result < 0 ? result : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_पढ़ो_all_indirect_csr_ctx(काष्ठा nfp_cpp *cpp,
			      काष्ठा nfp_dumpspec_csr *spec_csr, u32 address,
			      u32 reg_sz, व्योम *dest)
अणु
	u32 ctx;
	पूर्णांक err;

	क्रम (ctx = 0; ctx < NFP_IND_NUM_CONTEXTS; ctx++) अणु
		err = nfp_पढ़ो_indirect_csr(cpp, spec_csr->cpp.cpp_id, address,
					    reg_sz, ctx, dest + ctx * reg_sz);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_dump_indirect_csr_range(काष्ठा nfp_pf *pf,
			    काष्ठा nfp_dumpspec_csr *spec_csr,
			    काष्ठा nfp_dump_state *dump)
अणु
	काष्ठा nfp_dump_csr *dump_header = dump->p;
	u32 reg_sz, header_size, total_size;
	u32 cpp_rd_addr, max_rd_addr;
	u32 reg_data_length;
	व्योम *dest;
	पूर्णांक err;

	अगर (!nfp_csr_spec_valid(spec_csr))
		वापस nfp_dump_error_tlv(&spec_csr->tl, -EINVAL, dump);

	reg_sz = be32_to_cpu(spec_csr->रेजिस्टर_width) / BITS_PER_BYTE;
	header_size = ALIGN8(माप(*dump_header));
	reg_data_length = be32_to_cpu(spec_csr->cpp.dump_length) *
			  NFP_IND_NUM_CONTEXTS;
	total_size = header_size + ALIGN8(reg_data_length);
	dest = dump->p + header_size;

	err = nfp_add_tlv(be32_to_cpu(spec_csr->tl.type), total_size, dump);
	अगर (err)
		वापस err;

	dump_header->cpp = spec_csr->cpp;
	dump_header->रेजिस्टर_width = spec_csr->रेजिस्टर_width;

	cpp_rd_addr = be32_to_cpu(spec_csr->cpp.offset);
	max_rd_addr = cpp_rd_addr + be32_to_cpu(spec_csr->cpp.dump_length);
	जबतक (cpp_rd_addr < max_rd_addr) अणु
		err = nfp_पढ़ो_all_indirect_csr_ctx(pf->cpp, spec_csr,
						    cpp_rd_addr, reg_sz, dest);
		अगर (err) अणु
			dump_header->error = cpu_to_be32(err);
			dump_header->error_offset = cpu_to_be32(cpp_rd_addr);
			अवरोध;
		पूर्ण
		cpp_rd_addr += reg_sz;
		dest += reg_sz * NFP_IND_NUM_CONTEXTS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_dump_single_rtsym(काष्ठा nfp_pf *pf, काष्ठा nfp_dumpspec_rtsym *spec,
		      काष्ठा nfp_dump_state *dump)
अणु
	काष्ठा nfp_dump_rtsym *dump_header = dump->p;
	काष्ठा nfp_dumpspec_cpp_isl_id cpp_params;
	काष्ठा nfp_rtsym_table *rtbl = pf->rtbl;
	u32 header_size, total_size, sym_size;
	स्थिर काष्ठा nfp_rtsym *sym;
	u32 tl_len, key_len;
	पूर्णांक bytes_पढ़ो;
	व्योम *dest;
	पूर्णांक err;

	tl_len = be32_to_cpu(spec->tl.length);
	key_len = strnlen(spec->rtsym, tl_len);
	अगर (key_len == tl_len)
		वापस nfp_dump_error_tlv(&spec->tl, -EINVAL, dump);

	sym = nfp_rtsym_lookup(rtbl, spec->rtsym);
	अगर (!sym)
		वापस nfp_dump_error_tlv(&spec->tl, -ENOENT, dump);

	sym_size = nfp_rtsym_size(sym);
	header_size =
		ALIGN8(दुरत्व(काष्ठा nfp_dump_rtsym, rtsym) + key_len + 1);
	total_size = header_size + ALIGN8(sym_size);
	dest = dump->p + header_size;

	err = nfp_add_tlv(be32_to_cpu(spec->tl.type), total_size, dump);
	अगर (err)
		वापस err;

	dump_header->padded_name_length =
		header_size - दुरत्व(काष्ठा nfp_dump_rtsym, rtsym);
	स_नकल(dump_header->rtsym, spec->rtsym, key_len + 1);
	dump_header->cpp.dump_length = cpu_to_be32(sym_size);

	अगर (sym->type != NFP_RTSYM_TYPE_ABS) अणु
		cpp_params.target = sym->target;
		cpp_params.action = NFP_CPP_ACTION_RW;
		cpp_params.token  = 0;
		cpp_params.island = sym->करोमुख्य;
		dump_header->cpp.cpp_id = cpp_params;
		dump_header->cpp.offset = cpu_to_be32(sym->addr);
	पूर्ण

	bytes_पढ़ो = nfp_rtsym_पढ़ो(pf->cpp, sym, 0, dest, sym_size);
	अगर (bytes_पढ़ो != sym_size) अणु
		अगर (bytes_पढ़ो >= 0)
			bytes_पढ़ो = -EIO;
		dump_header->error = cpu_to_be32(bytes_पढ़ो);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_dump_क्रम_tlv(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_tl *tl, व्योम *param)
अणु
	काष्ठा nfp_dumpspec_rtsym *spec_rtsym;
	काष्ठा nfp_dump_state *dump = param;
	काष्ठा nfp_dumpspec_csr *spec_csr;
	पूर्णांक err;

	चयन (be32_to_cpu(tl->type)) अणु
	हाल NFP_DUMPSPEC_TYPE_FWNAME:
		err = nfp_dump_fwname(pf, dump);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_CPP_CSR:
	हाल NFP_DUMPSPEC_TYPE_XPB_CSR:
	हाल NFP_DUMPSPEC_TYPE_ME_CSR:
		spec_csr = (काष्ठा nfp_dumpspec_csr *)tl;
		err = nfp_dump_csr_range(pf, spec_csr, dump);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_INसूचीECT_ME_CSR:
		spec_csr = (काष्ठा nfp_dumpspec_csr *)tl;
		err = nfp_dump_indirect_csr_range(pf, spec_csr, dump);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_RTSYM:
		spec_rtsym = (काष्ठा nfp_dumpspec_rtsym *)tl;
		err = nfp_dump_single_rtsym(pf, spec_rtsym, dump);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_HWINFO:
		err = nfp_dump_hwinfo(pf, tl, dump);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NFP_DUMPSPEC_TYPE_HWINFO_FIELD:
		err = nfp_dump_hwinfo_field(pf, tl, dump);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		err = nfp_dump_error_tlv(tl, -EOPNOTSUPP, dump);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_dump_specअगरic_level(काष्ठा nfp_pf *pf, काष्ठा nfp_dump_tl *dump_level,
			व्योम *param)
अणु
	काष्ठा nfp_dump_state *dump = param;

	अगर (dump_level->type != dump->requested_level)
		वापस 0;

	वापस nfp_traverse_tlvs(pf, dump_level->data,
				 be32_to_cpu(dump_level->length), dump,
				 nfp_dump_क्रम_tlv);
पूर्ण

अटल पूर्णांक nfp_dump_populate_prolog(काष्ठा nfp_dump_state *dump)
अणु
	काष्ठा nfp_dump_prolog *prolog = dump->p;
	u32 total_size;
	पूर्णांक err;

	total_size = ALIGN8(माप(*prolog));

	err = nfp_add_tlv(NFP_DUMPSPEC_TYPE_PROLOG, total_size, dump);
	अगर (err)
		वापस err;

	prolog->dump_level = dump->requested_level;

	वापस 0;
पूर्ण

पूर्णांक nfp_net_dump_populate_buffer(काष्ठा nfp_pf *pf, काष्ठा nfp_dumpspec *spec,
				 काष्ठा ethtool_dump *dump_param, व्योम *dest)
अणु
	काष्ठा nfp_dump_state dump;
	पूर्णांक err;

	dump.requested_level = cpu_to_be32(dump_param->flag);
	dump.dumped_size = 0;
	dump.p = dest;
	dump.buf_size = dump_param->len;

	err = nfp_dump_populate_prolog(&dump);
	अगर (err)
		वापस err;

	err = nfp_traverse_tlvs(pf, spec->data, spec->size, &dump,
				nfp_dump_specअगरic_level);
	अगर (err)
		वापस err;

	/* Set size of actual dump, to trigger warning अगर dअगरferent from
	 * calculated size.
	 */
	dump_param->len = dump.dumped_size;

	वापस 0;
पूर्ण
