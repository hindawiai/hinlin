<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_rtsym.c
 * Interface क्रम accessing run-समय symbol table
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Espen Skoglund <espen.skoglund@netronome.com>
 *          Francois H. Theron <francois.theron@netronome.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/io-64-nonatomic-hi-lo.h>

#समावेश "nfp.h"
#समावेश "nfp_cpp.h"
#समावेश "nfp_nffw.h"
#समावेश "nfp6000/nfp6000.h"

/* These need to match the linker */
#घोषणा SYM_TGT_LMEM		0
#घोषणा SYM_TGT_EMU_CACHE	0x17

काष्ठा nfp_rtsym_entry अणु
	u8	type;
	u8	target;
	u8	island;
	u8	addr_hi;
	__le32	addr_lo;
	__le16	name;
	u8	mक्रमागत;
	u8	size_hi;
	__le32	size_lo;
पूर्ण;

काष्ठा nfp_rtsym_table अणु
	काष्ठा nfp_cpp *cpp;
	पूर्णांक num;
	अक्षर *strtab;
	काष्ठा nfp_rtsym symtab[];
पूर्ण;

अटल पूर्णांक nfp_meid(u8 island_id, u8 mक्रमागत)
अणु
	वापस (island_id & 0x3F) == island_id && mक्रमागत < 12 ?
		(island_id << 4) | (mक्रमागत + 4) : -1;
पूर्ण

अटल व्योम
nfp_rtsym_sw_entry_init(काष्ठा nfp_rtsym_table *cache, u32 strtab_size,
			काष्ठा nfp_rtsym *sw, काष्ठा nfp_rtsym_entry *fw)
अणु
	sw->type = fw->type;
	sw->name = cache->strtab + le16_to_cpu(fw->name) % strtab_size;
	sw->addr = ((u64)fw->addr_hi << 32) | le32_to_cpu(fw->addr_lo);
	sw->size = ((u64)fw->size_hi << 32) | le32_to_cpu(fw->size_lo);

	चयन (fw->target) अणु
	हाल SYM_TGT_LMEM:
		sw->target = NFP_RTSYM_TARGET_LMEM;
		अवरोध;
	हाल SYM_TGT_EMU_CACHE:
		sw->target = NFP_RTSYM_TARGET_EMU_CACHE;
		अवरोध;
	शेष:
		sw->target = fw->target;
		अवरोध;
	पूर्ण

	अगर (fw->mक्रमागत != 0xff)
		sw->करोमुख्य = nfp_meid(fw->island, fw->mक्रमागत);
	अन्यथा अगर (fw->island != 0xff)
		sw->करोमुख्य = fw->island;
	अन्यथा
		sw->करोमुख्य = -1;
पूर्ण

काष्ठा nfp_rtsym_table *nfp_rtsym_table_पढ़ो(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp_rtsym_table *rtbl;
	स्थिर काष्ठा nfp_mip *mip;

	mip = nfp_mip_खोलो(cpp);
	rtbl = __nfp_rtsym_table_पढ़ो(cpp, mip);
	nfp_mip_बंद(mip);

	वापस rtbl;
पूर्ण

काष्ठा nfp_rtsym_table *
__nfp_rtsym_table_पढ़ो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_mip *mip)
अणु
	स्थिर u32 dram = NFP_CPP_ID(NFP_CPP_TARGET_MU, NFP_CPP_ACTION_RW, 0) |
		NFP_ISL_EMEM0;
	u32 strtab_addr, symtab_addr, strtab_size, symtab_size;
	काष्ठा nfp_rtsym_entry *rtsymtab;
	काष्ठा nfp_rtsym_table *cache;
	पूर्णांक err, n, size;

	अगर (!mip)
		वापस शून्य;

	nfp_mip_strtab(mip, &strtab_addr, &strtab_size);
	nfp_mip_symtab(mip, &symtab_addr, &symtab_size);

	अगर (!symtab_size || !strtab_size || symtab_size % माप(*rtsymtab))
		वापस शून्य;

	/* Align to 64 bits */
	symtab_size = round_up(symtab_size, 8);
	strtab_size = round_up(strtab_size, 8);

	rtsymtab = kदो_स्मृति(symtab_size, GFP_KERNEL);
	अगर (!rtsymtab)
		वापस शून्य;

	size = माप(*cache);
	size += symtab_size / माप(*rtsymtab) * माप(काष्ठा nfp_rtsym);
	size +=	strtab_size + 1;
	cache = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!cache)
		जाओ निकास_मुक्त_rtsym_raw;

	cache->cpp = cpp;
	cache->num = symtab_size / माप(*rtsymtab);
	cache->strtab = (व्योम *)&cache->symtab[cache->num];

	err = nfp_cpp_पढ़ो(cpp, dram, symtab_addr, rtsymtab, symtab_size);
	अगर (err != symtab_size)
		जाओ निकास_मुक्त_cache;

	err = nfp_cpp_पढ़ो(cpp, dram, strtab_addr, cache->strtab, strtab_size);
	अगर (err != strtab_size)
		जाओ निकास_मुक्त_cache;
	cache->strtab[strtab_size] = '\0';

	क्रम (n = 0; n < cache->num; n++)
		nfp_rtsym_sw_entry_init(cache, strtab_size,
					&cache->symtab[n], &rtsymtab[n]);

	kमुक्त(rtsymtab);

	वापस cache;

निकास_मुक्त_cache:
	kमुक्त(cache);
निकास_मुक्त_rtsym_raw:
	kमुक्त(rtsymtab);
	वापस शून्य;
पूर्ण

/**
 * nfp_rtsym_count() - Get the number of RTSYM descriptors
 * @rtbl:	NFP RTsym table
 *
 * Return: Number of RTSYM descriptors
 */
पूर्णांक nfp_rtsym_count(काष्ठा nfp_rtsym_table *rtbl)
अणु
	अगर (!rtbl)
		वापस -EINVAL;
	वापस rtbl->num;
पूर्ण

/**
 * nfp_rtsym_get() - Get the Nth RTSYM descriptor
 * @rtbl:	NFP RTsym table
 * @idx:	Index (0-based) of the RTSYM descriptor
 *
 * Return: स्थिर poपूर्णांकer to a काष्ठा nfp_rtsym descriptor, or शून्य
 */
स्थिर काष्ठा nfp_rtsym *nfp_rtsym_get(काष्ठा nfp_rtsym_table *rtbl, पूर्णांक idx)
अणु
	अगर (!rtbl)
		वापस शून्य;
	अगर (idx >= rtbl->num)
		वापस शून्य;

	वापस &rtbl->symtab[idx];
पूर्ण

/**
 * nfp_rtsym_lookup() - Return the RTSYM descriptor क्रम a symbol name
 * @rtbl:	NFP RTsym table
 * @name:	Symbol name
 *
 * Return: स्थिर poपूर्णांकer to a काष्ठा nfp_rtsym descriptor, or शून्य
 */
स्थिर काष्ठा nfp_rtsym *
nfp_rtsym_lookup(काष्ठा nfp_rtsym_table *rtbl, स्थिर अक्षर *name)
अणु
	पूर्णांक n;

	अगर (!rtbl)
		वापस शून्य;

	क्रम (n = 0; n < rtbl->num; n++)
		अगर (म_भेद(name, rtbl->symtab[n].name) == 0)
			वापस &rtbl->symtab[n];

	वापस शून्य;
पूर्ण

u64 nfp_rtsym_size(स्थिर काष्ठा nfp_rtsym *sym)
अणु
	चयन (sym->type) अणु
	हाल NFP_RTSYM_TYPE_NONE:
		pr_err("rtsym '%s': type NONE\n", sym->name);
		वापस 0;
	शेष:
		pr_warn("rtsym '%s': unknown type: %d\n", sym->name, sym->type);
		fallthrough;
	हाल NFP_RTSYM_TYPE_OBJECT:
	हाल NFP_RTSYM_TYPE_FUNCTION:
		वापस sym->size;
	हाल NFP_RTSYM_TYPE_ABS:
		वापस माप(u64);
	पूर्ण
पूर्ण

अटल पूर्णांक
nfp_rtsym_to_dest(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		  u8 action, u8 token, u64 off, u32 *cpp_id, u64 *addr)
अणु
	अगर (sym->type != NFP_RTSYM_TYPE_OBJECT) अणु
		nfp_err(cpp, "rtsym '%s': direct access to non-object rtsym\n",
			sym->name);
		वापस -EINVAL;
	पूर्ण

	*addr = sym->addr + off;

	अगर (sym->target == NFP_RTSYM_TARGET_EMU_CACHE) अणु
		पूर्णांक locality_off = nfp_cpp_mu_locality_lsb(cpp);

		*addr &= ~(NFP_MU_ADDR_ACCESS_TYPE_MASK << locality_off);
		*addr |= NFP_MU_ADDR_ACCESS_TYPE_सूचीECT << locality_off;

		*cpp_id = NFP_CPP_ISLAND_ID(NFP_CPP_TARGET_MU, action, token,
					    sym->करोमुख्य);
	पूर्ण अन्यथा अगर (sym->target < 0) अणु
		nfp_err(cpp, "rtsym '%s': unhandled target encoding: %d\n",
			sym->name, sym->target);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		*cpp_id = NFP_CPP_ISLAND_ID(sym->target, action, token,
					    sym->करोमुख्य);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __nfp_rtsym_पढ़ो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		     u8 action, u8 token, u64 off, व्योम *buf, माप_प्रकार len)
अणु
	u64 sym_size = nfp_rtsym_size(sym);
	u32 cpp_id;
	u64 addr;
	पूर्णांक err;

	अगर (off > sym_size) अणु
		nfp_err(cpp, "rtsym '%s': read out of bounds: off: %lld + len: %zd > size: %lld\n",
			sym->name, off, len, sym_size);
		वापस -ENXIO;
	पूर्ण
	len = min_t(माप_प्रकार, len, sym_size - off);

	अगर (sym->type == NFP_RTSYM_TYPE_ABS) अणु
		u8 पंचांगp[8];

		put_unaligned_le64(sym->addr, पंचांगp);
		स_नकल(buf, &पंचांगp[off], len);

		वापस len;
	पूर्ण

	err = nfp_rtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addr);
	अगर (err)
		वापस err;

	वापस nfp_cpp_पढ़ो(cpp, cpp_id, addr, buf, len);
पूर्ण

पूर्णांक nfp_rtsym_पढ़ो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		   व्योम *buf, माप_प्रकार len)
अणु
	वापस __nfp_rtsym_पढ़ो(cpp, sym, NFP_CPP_ACTION_RW, 0, off, buf, len);
पूर्ण

पूर्णांक __nfp_rtsym_पढ़ोl(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		      u8 action, u8 token, u64 off, u32 *value)
अणु
	u32 cpp_id;
	u64 addr;
	पूर्णांक err;

	अगर (off + 4 > nfp_rtsym_size(sym)) अणु
		nfp_err(cpp, "rtsym '%s': readl out of bounds: off: %lld + 4 > size: %lld\n",
			sym->name, off, nfp_rtsym_size(sym));
		वापस -ENXIO;
	पूर्ण

	err = nfp_rtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addr);
	अगर (err)
		वापस err;

	वापस nfp_cpp_पढ़ोl(cpp, cpp_id, addr, value);
पूर्ण

पूर्णांक nfp_rtsym_पढ़ोl(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		    u32 *value)
अणु
	वापस __nfp_rtsym_पढ़ोl(cpp, sym, NFP_CPP_ACTION_RW, 0, off, value);
पूर्ण

पूर्णांक __nfp_rtsym_पढ़ोq(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		      u8 action, u8 token, u64 off, u64 *value)
अणु
	u32 cpp_id;
	u64 addr;
	पूर्णांक err;

	अगर (off + 8 > nfp_rtsym_size(sym)) अणु
		nfp_err(cpp, "rtsym '%s': readq out of bounds: off: %lld + 8 > size: %lld\n",
			sym->name, off, nfp_rtsym_size(sym));
		वापस -ENXIO;
	पूर्ण

	अगर (sym->type == NFP_RTSYM_TYPE_ABS) अणु
		*value = sym->addr;
		वापस 0;
	पूर्ण

	err = nfp_rtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addr);
	अगर (err)
		वापस err;

	वापस nfp_cpp_पढ़ोq(cpp, cpp_id, addr, value);
पूर्ण

पूर्णांक nfp_rtsym_पढ़ोq(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		    u64 *value)
अणु
	वापस __nfp_rtsym_पढ़ोq(cpp, sym, NFP_CPP_ACTION_RW, 0, off, value);
पूर्ण

पूर्णांक __nfp_rtsym_ग_लिखो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		      u8 action, u8 token, u64 off, व्योम *buf, माप_प्रकार len)
अणु
	u64 sym_size = nfp_rtsym_size(sym);
	u32 cpp_id;
	u64 addr;
	पूर्णांक err;

	अगर (off > sym_size) अणु
		nfp_err(cpp, "rtsym '%s': write out of bounds: off: %lld + len: %zd > size: %lld\n",
			sym->name, off, len, sym_size);
		वापस -ENXIO;
	पूर्ण
	len = min_t(माप_प्रकार, len, sym_size - off);

	err = nfp_rtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addr);
	अगर (err)
		वापस err;

	वापस nfp_cpp_ग_लिखो(cpp, cpp_id, addr, buf, len);
पूर्ण

पूर्णांक nfp_rtsym_ग_लिखो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		    व्योम *buf, माप_प्रकार len)
अणु
	वापस __nfp_rtsym_ग_लिखो(cpp, sym, NFP_CPP_ACTION_RW, 0, off, buf, len);
पूर्ण

पूर्णांक __nfp_rtsym_ग_लिखोl(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		       u8 action, u8 token, u64 off, u32 value)
अणु
	u32 cpp_id;
	u64 addr;
	पूर्णांक err;

	अगर (off + 4 > nfp_rtsym_size(sym)) अणु
		nfp_err(cpp, "rtsym '%s': writel out of bounds: off: %lld + 4 > size: %lld\n",
			sym->name, off, nfp_rtsym_size(sym));
		वापस -ENXIO;
	पूर्ण

	err = nfp_rtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addr);
	अगर (err)
		वापस err;

	वापस nfp_cpp_ग_लिखोl(cpp, cpp_id, addr, value);
पूर्ण

पूर्णांक nfp_rtsym_ग_लिखोl(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		     u32 value)
अणु
	वापस __nfp_rtsym_ग_लिखोl(cpp, sym, NFP_CPP_ACTION_RW, 0, off, value);
पूर्ण

पूर्णांक __nfp_rtsym_ग_लिखोq(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		       u8 action, u8 token, u64 off, u64 value)
अणु
	u32 cpp_id;
	u64 addr;
	पूर्णांक err;

	अगर (off + 8 > nfp_rtsym_size(sym)) अणु
		nfp_err(cpp, "rtsym '%s': writeq out of bounds: off: %lld + 8 > size: %lld\n",
			sym->name, off, nfp_rtsym_size(sym));
		वापस -ENXIO;
	पूर्ण

	err = nfp_rtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addr);
	अगर (err)
		वापस err;

	वापस nfp_cpp_ग_लिखोq(cpp, cpp_id, addr, value);
पूर्ण

पूर्णांक nfp_rtsym_ग_लिखोq(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		     u64 value)
अणु
	वापस __nfp_rtsym_ग_लिखोq(cpp, sym, NFP_CPP_ACTION_RW, 0, off, value);
पूर्ण

/**
 * nfp_rtsym_पढ़ो_le() - Read a simple अचिन्हित scalar value from symbol
 * @rtbl:	NFP RTsym table
 * @name:	Symbol name
 * @error:	Poniter to error code (optional)
 *
 * Lookup a symbol, map, पढ़ो it and वापस it's value. Value of the symbol
 * will be पूर्णांकerpreted as a simple little-endian अचिन्हित value. Symbol can
 * be 4 or 8 bytes in size.
 *
 * Return: value पढ़ो, on error sets the error and वापसs ~0ULL.
 */
u64 nfp_rtsym_पढ़ो_le(काष्ठा nfp_rtsym_table *rtbl, स्थिर अक्षर *name,
		      पूर्णांक *error)
अणु
	स्थिर काष्ठा nfp_rtsym *sym;
	u32 val32;
	u64 val;
	पूर्णांक err;

	sym = nfp_rtsym_lookup(rtbl, name);
	अगर (!sym) अणु
		err = -ENOENT;
		जाओ निकास;
	पूर्ण

	चयन (nfp_rtsym_size(sym)) अणु
	हाल 4:
		err = nfp_rtsym_पढ़ोl(rtbl->cpp, sym, 0, &val32);
		val = val32;
		अवरोध;
	हाल 8:
		err = nfp_rtsym_पढ़ोq(rtbl->cpp, sym, 0, &val);
		अवरोध;
	शेष:
		nfp_err(rtbl->cpp,
			"rtsym '%s': unsupported or non-scalar size: %lld\n",
			name, nfp_rtsym_size(sym));
		err = -EINVAL;
		अवरोध;
	पूर्ण

निकास:
	अगर (error)
		*error = err;

	अगर (err)
		वापस ~0ULL;
	वापस val;
पूर्ण

/**
 * nfp_rtsym_ग_लिखो_le() - Write an अचिन्हित scalar value to a symbol
 * @rtbl:	NFP RTsym table
 * @name:	Symbol name
 * @value:	Value to ग_लिखो
 *
 * Lookup a symbol and ग_लिखो a value to it. Symbol can be 4 or 8 bytes in size.
 * If 4 bytes then the lower 32-bits of 'value' are used. Value will be
 * written as simple little-endian अचिन्हित value.
 *
 * Return: 0 on success or error code.
 */
पूर्णांक nfp_rtsym_ग_लिखो_le(काष्ठा nfp_rtsym_table *rtbl, स्थिर अक्षर *name,
		       u64 value)
अणु
	स्थिर काष्ठा nfp_rtsym *sym;
	पूर्णांक err;

	sym = nfp_rtsym_lookup(rtbl, name);
	अगर (!sym)
		वापस -ENOENT;

	चयन (nfp_rtsym_size(sym)) अणु
	हाल 4:
		err = nfp_rtsym_ग_लिखोl(rtbl->cpp, sym, 0, value);
		अवरोध;
	हाल 8:
		err = nfp_rtsym_ग_लिखोq(rtbl->cpp, sym, 0, value);
		अवरोध;
	शेष:
		nfp_err(rtbl->cpp,
			"rtsym '%s': unsupported or non-scalar size: %lld\n",
			name, nfp_rtsym_size(sym));
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

u8 __iomem *
nfp_rtsym_map(काष्ठा nfp_rtsym_table *rtbl, स्थिर अक्षर *name, स्थिर अक्षर *id,
	      अचिन्हित पूर्णांक min_size, काष्ठा nfp_cpp_area **area)
अणु
	स्थिर काष्ठा nfp_rtsym *sym;
	u8 __iomem *mem;
	u32 cpp_id;
	u64 addr;
	पूर्णांक err;

	sym = nfp_rtsym_lookup(rtbl, name);
	अगर (!sym)
		वापस (u8 __iomem *)ERR_PTR(-ENOENT);

	err = nfp_rtsym_to_dest(rtbl->cpp, sym, NFP_CPP_ACTION_RW, 0, 0,
				&cpp_id, &addr);
	अगर (err) अणु
		nfp_err(rtbl->cpp, "rtsym '%s': mapping failed\n", name);
		वापस (u8 __iomem *)ERR_PTR(err);
	पूर्ण

	अगर (sym->size < min_size) अणु
		nfp_err(rtbl->cpp, "rtsym '%s': too small\n", name);
		वापस (u8 __iomem *)ERR_PTR(-EINVAL);
	पूर्ण

	mem = nfp_cpp_map_area(rtbl->cpp, id, cpp_id, addr, sym->size, area);
	अगर (IS_ERR(mem)) अणु
		nfp_err(rtbl->cpp, "rtysm '%s': failed to map: %ld\n",
			name, PTR_ERR(mem));
		वापस mem;
	पूर्ण

	वापस mem;
पूर्ण
