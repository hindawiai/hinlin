<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_cpplib.c
 * Library of functions to access the NFP's CPP bus
 * Authors: Jakub Kicinski <jakub.kicinski@netronome.com>
 *          Jason McMullan <jason.mcmullan@netronome.com>
 *          Rolf Neugebauer <rolf.neugebauer@netronome.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

#समावेश "nfp_cpp.h"
#समावेश "nfp6000/nfp6000.h"
#समावेश "nfp6000/nfp_xpb.h"

/* NFP6000 PL */
#घोषणा NFP_PL_DEVICE_ID			0x00000004
#घोषणा   NFP_PL_DEVICE_ID_MASK			GENMASK(7, 0)
#घोषणा   NFP_PL_DEVICE_PART_MASK		GENMASK(31, 16)
#घोषणा NFP_PL_DEVICE_MODEL_MASK		(NFP_PL_DEVICE_PART_MASK | \
						 NFP_PL_DEVICE_ID_MASK)

/**
 * nfp_cpp_पढ़ोl() - Read a u32 word from a CPP location
 * @cpp:	CPP device handle
 * @cpp_id:	CPP ID क्रम operation
 * @address:	Address क्रम operation
 * @value:	Poपूर्णांकer to पढ़ो buffer
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_cpp_पढ़ोl(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		  अचिन्हित दीर्घ दीर्घ address, u32 *value)
अणु
	u8 पंचांगp[4];
	पूर्णांक n;

	n = nfp_cpp_पढ़ो(cpp, cpp_id, address, पंचांगp, माप(पंचांगp));
	अगर (n != माप(पंचांगp))
		वापस n < 0 ? n : -EIO;

	*value = get_unaligned_le32(पंचांगp);
	वापस 0;
पूर्ण

/**
 * nfp_cpp_ग_लिखोl() - Write a u32 word to a CPP location
 * @cpp:	CPP device handle
 * @cpp_id:	CPP ID क्रम operation
 * @address:	Address क्रम operation
 * @value:	Value to ग_लिखो
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_cpp_ग_लिखोl(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		   अचिन्हित दीर्घ दीर्घ address, u32 value)
अणु
	u8 पंचांगp[4];
	पूर्णांक n;

	put_unaligned_le32(value, पंचांगp);
	n = nfp_cpp_ग_लिखो(cpp, cpp_id, address, पंचांगp, माप(पंचांगp));

	वापस n == माप(पंचांगp) ? 0 : n < 0 ? n : -EIO;
पूर्ण

/**
 * nfp_cpp_पढ़ोq() - Read a u64 word from a CPP location
 * @cpp:	CPP device handle
 * @cpp_id:	CPP ID क्रम operation
 * @address:	Address क्रम operation
 * @value:	Poपूर्णांकer to पढ़ो buffer
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_cpp_पढ़ोq(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		  अचिन्हित दीर्घ दीर्घ address, u64 *value)
अणु
	u8 पंचांगp[8];
	पूर्णांक n;

	n = nfp_cpp_पढ़ो(cpp, cpp_id, address, पंचांगp, माप(पंचांगp));
	अगर (n != माप(पंचांगp))
		वापस n < 0 ? n : -EIO;

	*value = get_unaligned_le64(पंचांगp);
	वापस 0;
पूर्ण

/**
 * nfp_cpp_ग_लिखोq() - Write a u64 word to a CPP location
 * @cpp:	CPP device handle
 * @cpp_id:	CPP ID क्रम operation
 * @address:	Address क्रम operation
 * @value:	Value to ग_लिखो
 *
 * Return: 0 on success, or -ERRNO
 */
पूर्णांक nfp_cpp_ग_लिखोq(काष्ठा nfp_cpp *cpp, u32 cpp_id,
		   अचिन्हित दीर्घ दीर्घ address, u64 value)
अणु
	u8 पंचांगp[8];
	पूर्णांक n;

	put_unaligned_le64(value, पंचांगp);
	n = nfp_cpp_ग_लिखो(cpp, cpp_id, address, पंचांगp, माप(पंचांगp));

	वापस n == माप(पंचांगp) ? 0 : n < 0 ? n : -EIO;
पूर्ण

/* NOTE: This code should not use nfp_xpb_* functions,
 * as those are model-specअगरic
 */
पूर्णांक nfp_cpp_model_स्वतःdetect(काष्ठा nfp_cpp *cpp, u32 *model)
अणु
	u32 reg;
	पूर्णांक err;

	err = nfp_xpb_पढ़ोl(cpp, NFP_XPB_DEVICE(1, 1, 16) + NFP_PL_DEVICE_ID,
			    &reg);
	अगर (err < 0)
		वापस err;

	*model = reg & NFP_PL_DEVICE_MODEL_MASK;
	अगर (*model & NFP_PL_DEVICE_ID_MASK)
		*model -= 0x10;

	वापस 0;
पूर्ण

अटल u8 nfp_bytemask(पूर्णांक width, u64 addr)
अणु
	अगर (width == 8)
		वापस 0xff;
	अन्यथा अगर (width == 4)
		वापस 0x0f << (addr & 4);
	अन्यथा अगर (width == 2)
		वापस 0x03 << (addr & 6);
	अन्यथा अगर (width == 1)
		वापस 0x01 << (addr & 7);
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक nfp_cpp_explicit_पढ़ो(काष्ठा nfp_cpp *cpp, u32 cpp_id,
			  u64 addr, व्योम *buff, माप_प्रकार len, पूर्णांक width_पढ़ो)
अणु
	काष्ठा nfp_cpp_explicit *expl;
	अक्षर *पंचांगp = buff;
	पूर्णांक err, i, incr;
	u8 byte_mask;

	अगर (len & (width_पढ़ो - 1))
		वापस -EINVAL;

	expl = nfp_cpp_explicit_acquire(cpp);
	अगर (!expl)
		वापस -EBUSY;

	incr = min_t(पूर्णांक, 16 * width_पढ़ो, 128);
	incr = min_t(पूर्णांक, incr, len);

	/* Translate a NFP_CPP_ACTION_RW to action 0 */
	अगर (NFP_CPP_ID_ACTION_of(cpp_id) == NFP_CPP_ACTION_RW)
		cpp_id = NFP_CPP_ID(NFP_CPP_ID_TARGET_of(cpp_id), 0,
				    NFP_CPP_ID_TOKEN_of(cpp_id));

	byte_mask = nfp_bytemask(width_पढ़ो, addr);

	nfp_cpp_explicit_set_target(expl, cpp_id,
				    incr / width_पढ़ो - 1, byte_mask);
	nfp_cpp_explicit_set_posted(expl, 1, 0, NFP_SIGNAL_PUSH,
				    0, NFP_SIGNAL_NONE);

	क्रम (i = 0; i < len; i += incr, addr += incr, पंचांगp += incr) अणु
		अगर (i + incr > len) अणु
			incr = len - i;
			nfp_cpp_explicit_set_target(expl, cpp_id,
						    incr / width_पढ़ो - 1,
						    0xff);
		पूर्ण

		err = nfp_cpp_explicit_करो(expl, addr);
		अगर (err < 0)
			जाओ निकास_release;

		err = nfp_cpp_explicit_get(expl, पंचांगp, incr);
		अगर (err < 0)
			जाओ निकास_release;
	पूर्ण
	err = len;
निकास_release:
	nfp_cpp_explicit_release(expl);

	वापस err;
पूर्ण

पूर्णांक nfp_cpp_explicit_ग_लिखो(काष्ठा nfp_cpp *cpp, u32 cpp_id, u64 addr,
			   स्थिर व्योम *buff, माप_प्रकार len, पूर्णांक width_ग_लिखो)
अणु
	काष्ठा nfp_cpp_explicit *expl;
	स्थिर अक्षर *पंचांगp = buff;
	पूर्णांक err, i, incr;
	u8 byte_mask;

	अगर (len & (width_ग_लिखो - 1))
		वापस -EINVAL;

	expl = nfp_cpp_explicit_acquire(cpp);
	अगर (!expl)
		वापस -EBUSY;

	incr = min_t(पूर्णांक, 16 * width_ग_लिखो, 128);
	incr = min_t(पूर्णांक, incr, len);

	/* Translate a NFP_CPP_ACTION_RW to action 1 */
	अगर (NFP_CPP_ID_ACTION_of(cpp_id) == NFP_CPP_ACTION_RW)
		cpp_id = NFP_CPP_ID(NFP_CPP_ID_TARGET_of(cpp_id), 1,
				    NFP_CPP_ID_TOKEN_of(cpp_id));

	byte_mask = nfp_bytemask(width_ग_लिखो, addr);

	nfp_cpp_explicit_set_target(expl, cpp_id,
				    incr / width_ग_लिखो - 1, byte_mask);
	nfp_cpp_explicit_set_posted(expl, 1, 0, NFP_SIGNAL_PULL,
				    0, NFP_SIGNAL_NONE);

	क्रम (i = 0; i < len; i += incr, addr += incr, पंचांगp += incr) अणु
		अगर (i + incr > len) अणु
			incr = len - i;
			nfp_cpp_explicit_set_target(expl, cpp_id,
						    incr / width_ग_लिखो - 1,
						    0xff);
		पूर्ण

		err = nfp_cpp_explicit_put(expl, पंचांगp, incr);
		अगर (err < 0)
			जाओ निकास_release;

		err = nfp_cpp_explicit_करो(expl, addr);
		अगर (err < 0)
			जाओ निकास_release;
	पूर्ण
	err = len;
निकास_release:
	nfp_cpp_explicit_release(expl);

	वापस err;
पूर्ण

/**
 * nfp_cpp_map_area() - Helper function to map an area
 * @cpp:    NFP CPP handler
 * @name:   Name क्रम the area
 * @cpp_id: CPP ID क्रम operation
 * @addr:   CPP address
 * @size:   Size of the area
 * @area:   Area handle (output)
 *
 * Map an area of IOMEM access.  To unकरो the effect of this function call
 * @nfp_cpp_area_release_मुक्त(*area).
 *
 * Return: Poपूर्णांकer to memory mapped area or ERR_PTR
 */
u8 __iomem *
nfp_cpp_map_area(काष्ठा nfp_cpp *cpp, स्थिर अक्षर *name, u32 cpp_id, u64 addr,
		 अचिन्हित दीर्घ size, काष्ठा nfp_cpp_area **area)
अणु
	u8 __iomem *res;

	*area = nfp_cpp_area_alloc_acquire(cpp, name, cpp_id, addr, size);
	अगर (!*area)
		जाओ err_eio;

	res = nfp_cpp_area_iomem(*area);
	अगर (!res)
		जाओ err_release_मुक्त;

	वापस res;

err_release_मुक्त:
	nfp_cpp_area_release_मुक्त(*area);
err_eio:
	वापस (u8 __iomem *)ERR_PTR(-EIO);
पूर्ण
