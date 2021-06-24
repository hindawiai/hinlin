<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_nffw.c
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Francois H. Theron <francois.theron@netronome.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "nfp.h"
#समावेश "nfp_cpp.h"
#समावेश "nfp_nffw.h"
#समावेश "nfp6000/nfp6000.h"

/* Init-CSR owner IDs क्रम firmware map to firmware IDs which start at 4.
 * Lower IDs are reserved क्रम target and loader IDs.
 */
#घोषणा NFFW_FWID_EXT   3 /* For active MEs that we didn't load. */
#घोषणा NFFW_FWID_BASE  4

#घोषणा NFFW_FWID_ALL   255

/**
 * NFFW_INFO_VERSION history:
 * 0: This was never actually used (beक्रमe versioning), but it refers to
 *    the previous काष्ठा which had FWINFO_CNT = MEINFO_CNT = 120 that later
 *    changed to 200.
 * 1: First versioned काष्ठा, with
 *     FWINFO_CNT = 120
 *     MEINFO_CNT = 120
 * 2:  FWINFO_CNT = 200
 *     MEINFO_CNT = 200
 */
#घोषणा NFFW_INFO_VERSION_CURRENT 2

/* Enough क्रम all current chip families */
#घोषणा NFFW_MEINFO_CNT_V1 120
#घोषणा NFFW_FWINFO_CNT_V1 120
#घोषणा NFFW_MEINFO_CNT_V2 200
#घोषणा NFFW_FWINFO_CNT_V2 200

/* Work in 32-bit words to make cross-platक्रमm endianness easier to handle */

/** nfp.nffw meinfo **/
काष्ठा nffw_meinfo अणु
	__le32 ctxmask__fwid__meid;
पूर्ण;

काष्ठा nffw_fwinfo अणु
	__le32 loaded__mu_da__mip_off_hi;
	__le32 mip_cppid; /* 0 means no MIP */
	__le32 mip_offset_lo;
पूर्ण;

काष्ठा nfp_nffw_info_v1 अणु
	काष्ठा nffw_meinfo meinfo[NFFW_MEINFO_CNT_V1];
	काष्ठा nffw_fwinfo fwinfo[NFFW_FWINFO_CNT_V1];
पूर्ण;

काष्ठा nfp_nffw_info_v2 अणु
	काष्ठा nffw_meinfo meinfo[NFFW_MEINFO_CNT_V2];
	काष्ठा nffw_fwinfo fwinfo[NFFW_FWINFO_CNT_V2];
पूर्ण;

/** Resource: nfp.nffw मुख्य **/
काष्ठा nfp_nffw_info_data अणु
	__le32 flags[2];
	जोड़ अणु
		काष्ठा nfp_nffw_info_v1 v1;
		काष्ठा nfp_nffw_info_v2 v2;
	पूर्ण info;
पूर्ण;

काष्ठा nfp_nffw_info अणु
	काष्ठा nfp_cpp *cpp;
	काष्ठा nfp_resource *res;

	काष्ठा nfp_nffw_info_data fwinf;
पूर्ण;

/* flg_info_version = flags[0]<27:16>
 * This is a small version counter पूर्णांकended only to detect अगर the current
 * implementation can पढ़ो the current काष्ठा. Struct changes should be very
 * rare and as such a 12-bit counter should cover large spans of समय. By the
 * समय it wraps around, we करोn't expect to have 4096 versions of this काष्ठा
 * to be in use at the same समय.
 */
अटल u32 nffw_res_info_version_get(स्थिर काष्ठा nfp_nffw_info_data *res)
अणु
	वापस (le32_to_cpu(res->flags[0]) >> 16) & 0xfff;
पूर्ण

/* flg_init = flags[0]<0> */
अटल u32 nffw_res_flg_init_get(स्थिर काष्ठा nfp_nffw_info_data *res)
अणु
	वापस (le32_to_cpu(res->flags[0]) >> 0) & 1;
पूर्ण

/* loaded = loaded__mu_da__mip_off_hi<31:31> */
अटल u32 nffw_fwinfo_loaded_get(स्थिर काष्ठा nffw_fwinfo *fi)
अणु
	वापस (le32_to_cpu(fi->loaded__mu_da__mip_off_hi) >> 31) & 1;
पूर्ण

/* mip_cppid = mip_cppid */
अटल u32 nffw_fwinfo_mip_cppid_get(स्थिर काष्ठा nffw_fwinfo *fi)
अणु
	वापस le32_to_cpu(fi->mip_cppid);
पूर्ण

/* loaded = loaded__mu_da__mip_off_hi<8:8> */
अटल u32 nffw_fwinfo_mip_mu_da_get(स्थिर काष्ठा nffw_fwinfo *fi)
अणु
	वापस (le32_to_cpu(fi->loaded__mu_da__mip_off_hi) >> 8) & 1;
पूर्ण

/* mip_offset = (loaded__mu_da__mip_off_hi<7:0> << 8) | mip_offset_lo */
अटल u64 nffw_fwinfo_mip_offset_get(स्थिर काष्ठा nffw_fwinfo *fi)
अणु
	u64 mip_off_hi = le32_to_cpu(fi->loaded__mu_da__mip_off_hi);

	वापस (mip_off_hi & 0xFF) << 32 | le32_to_cpu(fi->mip_offset_lo);
पूर्ण

अटल अचिन्हित पूर्णांक
nffw_res_fwinfos(काष्ठा nfp_nffw_info_data *fwinf, काष्ठा nffw_fwinfo **arr)
अणु
	/* For the this code, version 0 is most likely to be
	 * version 1 in this हाल. Since the kernel driver
	 * करोes not take responsibility क्रम initialising the
	 * nfp.nffw resource, any previous code (CA firmware or
	 * userspace) that left the version 0 and did set
	 * the init flag is going to be version 1.
	 */
	चयन (nffw_res_info_version_get(fwinf)) अणु
	हाल 0:
	हाल 1:
		*arr = &fwinf->info.v1.fwinfo[0];
		वापस NFFW_FWINFO_CNT_V1;
	हाल 2:
		*arr = &fwinf->info.v2.fwinfo[0];
		वापस NFFW_FWINFO_CNT_V2;
	शेष:
		*arr = शून्य;
		वापस 0;
	पूर्ण
पूर्ण

/**
 * nfp_nffw_info_खोलो() - Acquire the lock on the NFFW table
 * @cpp:	NFP CPP handle
 *
 * Return: poपूर्णांकer to nfp_nffw_info object or ERR_PTR()
 */
काष्ठा nfp_nffw_info *nfp_nffw_info_खोलो(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp_nffw_info_data *fwinf;
	काष्ठा nfp_nffw_info *state;
	u32 info_ver;
	पूर्णांक err;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस ERR_PTR(-ENOMEM);

	state->res = nfp_resource_acquire(cpp, NFP_RESOURCE_NFP_NFFW);
	अगर (IS_ERR(state->res))
		जाओ err_मुक्त;

	fwinf = &state->fwinf;

	अगर (माप(*fwinf) > nfp_resource_size(state->res))
		जाओ err_release;

	err = nfp_cpp_पढ़ो(cpp, nfp_resource_cpp_id(state->res),
			   nfp_resource_address(state->res),
			   fwinf, माप(*fwinf));
	अगर (err < (पूर्णांक)माप(*fwinf))
		जाओ err_release;

	अगर (!nffw_res_flg_init_get(fwinf))
		जाओ err_release;

	info_ver = nffw_res_info_version_get(fwinf);
	अगर (info_ver > NFFW_INFO_VERSION_CURRENT)
		जाओ err_release;

	state->cpp = cpp;
	वापस state;

err_release:
	nfp_resource_release(state->res);
err_मुक्त:
	kमुक्त(state);
	वापस ERR_PTR(-EIO);
पूर्ण

/**
 * nfp_nffw_info_बंद() - Release the lock on the NFFW table and मुक्त state
 * @state:	NFP FW info state
 */
व्योम nfp_nffw_info_बंद(काष्ठा nfp_nffw_info *state)
अणु
	nfp_resource_release(state->res);
	kमुक्त(state);
पूर्ण

/**
 * nfp_nffw_info_fwid_first() - Return the first firmware ID in the NFFW
 * @state:	NFP FW info state
 *
 * Return: First NFFW firmware info, शून्य on failure
 */
अटल काष्ठा nffw_fwinfo *nfp_nffw_info_fwid_first(काष्ठा nfp_nffw_info *state)
अणु
	काष्ठा nffw_fwinfo *fwinfo;
	अचिन्हित पूर्णांक cnt, i;

	cnt = nffw_res_fwinfos(&state->fwinf, &fwinfo);
	अगर (!cnt)
		वापस शून्य;

	क्रम (i = 0; i < cnt; i++)
		अगर (nffw_fwinfo_loaded_get(&fwinfo[i]))
			वापस &fwinfo[i];

	वापस शून्य;
पूर्ण

/**
 * nfp_nffw_info_mip_first() - Retrieve the location of the first FW's MIP
 * @state:	NFP FW info state
 * @cpp_id:	Poपूर्णांकer to the CPP ID of the MIP
 * @off:	Poपूर्णांकer to the CPP Address of the MIP
 *
 * Return: 0, or -ERRNO
 */
पूर्णांक nfp_nffw_info_mip_first(काष्ठा nfp_nffw_info *state, u32 *cpp_id, u64 *off)
अणु
	काष्ठा nffw_fwinfo *fwinfo;

	fwinfo = nfp_nffw_info_fwid_first(state);
	अगर (!fwinfo)
		वापस -EINVAL;

	*cpp_id = nffw_fwinfo_mip_cppid_get(fwinfo);
	*off = nffw_fwinfo_mip_offset_get(fwinfo);

	अगर (nffw_fwinfo_mip_mu_da_get(fwinfo)) अणु
		पूर्णांक locality_off = nfp_cpp_mu_locality_lsb(state->cpp);

		*off &= ~(NFP_MU_ADDR_ACCESS_TYPE_MASK << locality_off);
		*off |= NFP_MU_ADDR_ACCESS_TYPE_सूचीECT << locality_off;
	पूर्ण

	वापस 0;
पूर्ण
