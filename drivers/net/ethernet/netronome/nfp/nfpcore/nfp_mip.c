<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2017 Netronome Systems, Inc. */

/*
 * nfp_mip.c
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Espen Skoglund <espen.skoglund@netronome.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "nfp.h"
#समावेश "nfp_cpp.h"
#समावेश "nfp_nffw.h"

#घोषणा NFP_MIP_SIGNATURE	cpu_to_le32(0x0050494d)  /* "MIP\0" */
#घोषणा NFP_MIP_VERSION		cpu_to_le32(1)
#घोषणा NFP_MIP_MAX_OFFSET	(256 * 1024)

काष्ठा nfp_mip अणु
	__le32 signature;
	__le32 mip_version;
	__le32 mip_size;
	__le32 first_entry;

	__le32 version;
	__le32 buildnum;
	__le32 buildसमय;
	__le32 loadसमय;

	__le32 symtab_addr;
	__le32 symtab_size;
	__le32 strtab_addr;
	__le32 strtab_size;

	अक्षर name[16];
	अक्षर toolchain[32];
पूर्ण;

/* Read memory and check अगर it could be a valid MIP */
अटल पूर्णांक
nfp_mip_try_पढ़ो(काष्ठा nfp_cpp *cpp, u32 cpp_id, u64 addr, काष्ठा nfp_mip *mip)
अणु
	पूर्णांक ret;

	ret = nfp_cpp_पढ़ो(cpp, cpp_id, addr, mip, माप(*mip));
	अगर (ret != माप(*mip)) अणु
		nfp_err(cpp, "Failed to read MIP data (%d, %zu)\n",
			ret, माप(*mip));
		वापस -EIO;
	पूर्ण
	अगर (mip->signature != NFP_MIP_SIGNATURE) अणु
		nfp_warn(cpp, "Incorrect MIP signature (0x%08x)\n",
			 le32_to_cpu(mip->signature));
		वापस -EINVAL;
	पूर्ण
	अगर (mip->mip_version != NFP_MIP_VERSION) अणु
		nfp_warn(cpp, "Unsupported MIP version (%d)\n",
			 le32_to_cpu(mip->mip_version));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Try to locate MIP using the resource table */
अटल पूर्णांक nfp_mip_पढ़ो_resource(काष्ठा nfp_cpp *cpp, काष्ठा nfp_mip *mip)
अणु
	काष्ठा nfp_nffw_info *nffw_info;
	u32 cpp_id;
	u64 addr;
	पूर्णांक err;

	nffw_info = nfp_nffw_info_खोलो(cpp);
	अगर (IS_ERR(nffw_info))
		वापस PTR_ERR(nffw_info);

	err = nfp_nffw_info_mip_first(nffw_info, &cpp_id, &addr);
	अगर (err)
		जाओ निकास_बंद_nffw;

	err = nfp_mip_try_पढ़ो(cpp, cpp_id, addr, mip);
निकास_बंद_nffw:
	nfp_nffw_info_बंद(nffw_info);
	वापस err;
पूर्ण

/**
 * nfp_mip_खोलो() - Get device MIP काष्ठाure
 * @cpp:	NFP CPP Handle
 *
 * Copy MIP काष्ठाure from NFP device and वापस it.  The वापसed
 * काष्ठाure is handled पूर्णांकernally by the library and should be
 * मुक्तd by calling nfp_mip_बंद().
 *
 * Return: poपूर्णांकer to mip, शून्य on failure.
 */
स्थिर काष्ठा nfp_mip *nfp_mip_खोलो(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp_mip *mip;
	पूर्णांक err;

	mip = kदो_स्मृति(माप(*mip), GFP_KERNEL);
	अगर (!mip)
		वापस शून्य;

	err = nfp_mip_पढ़ो_resource(cpp, mip);
	अगर (err) अणु
		kमुक्त(mip);
		वापस शून्य;
	पूर्ण

	mip->name[माप(mip->name) - 1] = 0;

	वापस mip;
पूर्ण

व्योम nfp_mip_बंद(स्थिर काष्ठा nfp_mip *mip)
अणु
	kमुक्त(mip);
पूर्ण

स्थिर अक्षर *nfp_mip_name(स्थिर काष्ठा nfp_mip *mip)
अणु
	वापस mip->name;
पूर्ण

/**
 * nfp_mip_symtab() - Get the address and size of the MIP symbol table
 * @mip:	MIP handle
 * @addr:	Location क्रम NFP DDR address of MIP symbol table
 * @size:	Location क्रम size of MIP symbol table
 */
व्योम nfp_mip_symtab(स्थिर काष्ठा nfp_mip *mip, u32 *addr, u32 *size)
अणु
	*addr = le32_to_cpu(mip->symtab_addr);
	*size = le32_to_cpu(mip->symtab_size);
पूर्ण

/**
 * nfp_mip_strtab() - Get the address and size of the MIP symbol name table
 * @mip:	MIP handle
 * @addr:	Location क्रम NFP DDR address of MIP symbol name table
 * @size:	Location क्रम size of MIP symbol name table
 */
व्योम nfp_mip_strtab(स्थिर काष्ठा nfp_mip *mip, u32 *addr, u32 *size)
अणु
	*addr = le32_to_cpu(mip->strtab_addr);
	*size = le32_to_cpu(mip->strtab_size);
पूर्ण
