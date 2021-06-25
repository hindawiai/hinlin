<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * hvconsole.c
 * Copyright (C) 2004 Hollis Blanअक्षरd, IBM Corporation
 * Copyright (C) 2004 IBM Corporation
 *
 * Additional Author(s):
 *  Ryan S. Arnold <rsa@us.ibm.com>
 *
 * LPAR console support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/hvconsole.h>
#समावेश <यंत्र/plpar_wrappers.h>

/**
 * hvc_get_अक्षरs - retrieve अक्षरacters from firmware क्रम denoted vterm adapter
 * @vtermno: The vtermno or unit_address of the adapter from which to fetch the
 *	data.
 * @buf: The अक्षरacter buffer पूर्णांकo which to put the अक्षरacter data fetched from
 *	firmware.
 * @count: not used?
 */
पूर्णांक hvc_get_अक्षरs(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count)
अणु
	दीर्घ ret;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	अचिन्हित दीर्घ *lbuf = (अचिन्हित दीर्घ *)buf;

	ret = plpar_hcall(H_GET_TERM_CHAR, retbuf, vtermno);
	lbuf[0] = be64_to_cpu(retbuf[1]);
	lbuf[1] = be64_to_cpu(retbuf[2]);

	अगर (ret == H_SUCCESS)
		वापस retbuf[0];

	वापस 0;
पूर्ण

EXPORT_SYMBOL(hvc_get_अक्षरs);


/**
 * hvc_put_अक्षरs: send अक्षरacters to firmware क्रम denoted vterm adapter
 * @vtermno: The vtermno or unit_address of the adapter from which the data
 *	originated.
 * @buf: The अक्षरacter buffer that contains the अक्षरacter data to send to
 *	firmware. Must be at least 16 bytes, even अगर count is less than 16.
 * @count: Send this number of अक्षरacters.
 */
पूर्णांक hvc_put_अक्षरs(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	अचिन्हित दीर्घ *lbuf = (अचिन्हित दीर्घ *) buf;
	दीर्घ ret;


	/* hcall will ret H_PARAMETER अगर 'count' exceeds firmware max.*/
	अगर (count > MAX_VIO_PUT_CHARS)
		count = MAX_VIO_PUT_CHARS;

	ret = plpar_hcall_norets(H_PUT_TERM_CHAR, vtermno, count,
				 cpu_to_be64(lbuf[0]),
				 cpu_to_be64(lbuf[1]));
	अगर (ret == H_SUCCESS)
		वापस count;
	अगर (ret == H_BUSY)
		वापस -EAGAIN;
	वापस -EIO;
पूर्ण

EXPORT_SYMBOL(hvc_put_अक्षरs);
