<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_nffw.h
 * Authors: Jason McMullan <jason.mcmullan@netronome.com>
 *          Francois H. Theron <francois.theron@netronome.com>
 */

#अगर_अघोषित NFP_NFFW_H
#घोषणा NFP_NFFW_H

/* Implemented in nfp_nffw.c */

काष्ठा nfp_nffw_info;

काष्ठा nfp_nffw_info *nfp_nffw_info_खोलो(काष्ठा nfp_cpp *cpp);
व्योम nfp_nffw_info_बंद(काष्ठा nfp_nffw_info *state);
पूर्णांक nfp_nffw_info_mip_first(काष्ठा nfp_nffw_info *state, u32 *cpp_id, u64 *off);

/* Implemented in nfp_mip.c */

काष्ठा nfp_mip;

स्थिर काष्ठा nfp_mip *nfp_mip_खोलो(काष्ठा nfp_cpp *cpp);
व्योम nfp_mip_बंद(स्थिर काष्ठा nfp_mip *mip);

स्थिर अक्षर *nfp_mip_name(स्थिर काष्ठा nfp_mip *mip);
व्योम nfp_mip_symtab(स्थिर काष्ठा nfp_mip *mip, u32 *addr, u32 *size);
व्योम nfp_mip_strtab(स्थिर काष्ठा nfp_mip *mip, u32 *addr, u32 *size);

/* Implemented in nfp_rtsym.c */

क्रमागत nfp_rtsym_type अणु
	NFP_RTSYM_TYPE_NONE	= 0,
	NFP_RTSYM_TYPE_OBJECT	= 1,
	NFP_RTSYM_TYPE_FUNCTION	= 2,
	NFP_RTSYM_TYPE_ABS	= 3,
पूर्ण;

#घोषणा NFP_RTSYM_TARGET_NONE		0
#घोषणा NFP_RTSYM_TARGET_LMEM		-1
#घोषणा NFP_RTSYM_TARGET_EMU_CACHE	-7

/**
 * काष्ठा nfp_rtsym - RTSYM descriptor
 * @name:	Symbol name
 * @addr:	Address in the करोमुख्य/target's address space
 * @size:	Size (in bytes) of the symbol
 * @type:	NFP_RTSYM_TYPE_* of the symbol
 * @target:	CPP Target identअगरier, or NFP_RTSYM_TARGET_*
 * @करोमुख्य:	CPP Target Doमुख्य (island)
 */
काष्ठा nfp_rtsym अणु
	स्थिर अक्षर *name;
	u64 addr;
	u64 size;
	क्रमागत nfp_rtsym_type type;
	पूर्णांक target;
	पूर्णांक करोमुख्य;
पूर्ण;

काष्ठा nfp_rtsym_table;

काष्ठा nfp_rtsym_table *nfp_rtsym_table_पढ़ो(काष्ठा nfp_cpp *cpp);
काष्ठा nfp_rtsym_table *
__nfp_rtsym_table_पढ़ो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_mip *mip);
पूर्णांक nfp_rtsym_count(काष्ठा nfp_rtsym_table *rtbl);
स्थिर काष्ठा nfp_rtsym *nfp_rtsym_get(काष्ठा nfp_rtsym_table *rtbl, पूर्णांक idx);
स्थिर काष्ठा nfp_rtsym *
nfp_rtsym_lookup(काष्ठा nfp_rtsym_table *rtbl, स्थिर अक्षर *name);

u64 nfp_rtsym_size(स्थिर काष्ठा nfp_rtsym *rtsym);
पूर्णांक __nfp_rtsym_पढ़ो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		     u8 action, u8 token, u64 off, व्योम *buf, माप_प्रकार len);
पूर्णांक nfp_rtsym_पढ़ो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		   व्योम *buf, माप_प्रकार len);
पूर्णांक __nfp_rtsym_पढ़ोl(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		      u8 action, u8 token, u64 off, u32 *value);
पूर्णांक nfp_rtsym_पढ़ोl(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		    u32 *value);
पूर्णांक __nfp_rtsym_पढ़ोq(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		      u8 action, u8 token, u64 off, u64 *value);
पूर्णांक nfp_rtsym_पढ़ोq(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		    u64 *value);
पूर्णांक __nfp_rtsym_ग_लिखो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		      u8 action, u8 token, u64 off, व्योम *buf, माप_प्रकार len);
पूर्णांक nfp_rtsym_ग_लिखो(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		    व्योम *buf, माप_प्रकार len);
पूर्णांक __nfp_rtsym_ग_लिखोl(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		       u8 action, u8 token, u64 off, u32 value);
पूर्णांक nfp_rtsym_ग_लिखोl(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		     u32 value);
पूर्णांक __nfp_rtsym_ग_लिखोq(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym,
		       u8 action, u8 token, u64 off, u64 value);
पूर्णांक nfp_rtsym_ग_लिखोq(काष्ठा nfp_cpp *cpp, स्थिर काष्ठा nfp_rtsym *sym, u64 off,
		     u64 value);

u64 nfp_rtsym_पढ़ो_le(काष्ठा nfp_rtsym_table *rtbl, स्थिर अक्षर *name,
		      पूर्णांक *error);
पूर्णांक nfp_rtsym_ग_लिखो_le(काष्ठा nfp_rtsym_table *rtbl, स्थिर अक्षर *name,
		       u64 value);
u8 __iomem *
nfp_rtsym_map(काष्ठा nfp_rtsym_table *rtbl, स्थिर अक्षर *name, स्थिर अक्षर *id,
	      अचिन्हित पूर्णांक min_size, काष्ठा nfp_cpp_area **area);

#पूर्ण_अगर /* NFP_NFFW_H */
