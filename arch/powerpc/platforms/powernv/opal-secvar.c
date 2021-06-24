<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PowerNV code क्रम secure variables
 *
 * Copyright (C) 2019 IBM Corporation
 * Author: Claudio Carvalho
 *         Nayna Jain
 *
 * APIs to access secure variables managed by OPAL.
 */

#घोषणा pr_fmt(fmt) "secvar: "fmt

#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/secvar.h>
#समावेश <यंत्र/secure_boot.h>

अटल पूर्णांक opal_status_to_err(पूर्णांक rc)
अणु
	पूर्णांक err;

	चयन (rc) अणु
	हाल OPAL_SUCCESS:
		err = 0;
		अवरोध;
	हाल OPAL_UNSUPPORTED:
		err = -ENXIO;
		अवरोध;
	हाल OPAL_PARAMETER:
		err = -EINVAL;
		अवरोध;
	हाल OPAL_RESOURCE:
		err = -ENOSPC;
		अवरोध;
	हाल OPAL_HARDWARE:
		err = -EIO;
		अवरोध;
	हाल OPAL_NO_MEM:
		err = -ENOMEM;
		अवरोध;
	हाल OPAL_EMPTY:
		err = -ENOENT;
		अवरोध;
	हाल OPAL_PARTIAL:
		err = -EFBIG;
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक opal_get_variable(स्थिर अक्षर *key, uपूर्णांक64_t ksize,
			     u8 *data, uपूर्णांक64_t *dsize)
अणु
	पूर्णांक rc;

	अगर (!key || !dsize)
		वापस -EINVAL;

	*dsize = cpu_to_be64(*dsize);

	rc = opal_secvar_get(key, ksize, data, dsize);

	*dsize = be64_to_cpu(*dsize);

	वापस opal_status_to_err(rc);
पूर्ण

अटल पूर्णांक opal_get_next_variable(स्थिर अक्षर *key, uपूर्णांक64_t *keylen,
				  uपूर्णांक64_t keybufsize)
अणु
	पूर्णांक rc;

	अगर (!key || !keylen)
		वापस -EINVAL;

	*keylen = cpu_to_be64(*keylen);

	rc = opal_secvar_get_next(key, keylen, keybufsize);

	*keylen = be64_to_cpu(*keylen);

	वापस opal_status_to_err(rc);
पूर्ण

अटल पूर्णांक opal_set_variable(स्थिर अक्षर *key, uपूर्णांक64_t ksize, u8 *data,
			     uपूर्णांक64_t dsize)
अणु
	पूर्णांक rc;

	अगर (!key || !data)
		वापस -EINVAL;

	rc = opal_secvar_enqueue_update(key, ksize, data, dsize);

	वापस opal_status_to_err(rc);
पूर्ण

अटल स्थिर काष्ठा secvar_operations opal_secvar_ops = अणु
	.get = opal_get_variable,
	.get_next = opal_get_next_variable,
	.set = opal_set_variable,
पूर्ण;

अटल पूर्णांक opal_secvar_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (!opal_check_token(OPAL_SECVAR_GET)
			|| !opal_check_token(OPAL_SECVAR_GET_NEXT)
			|| !opal_check_token(OPAL_SECVAR_ENQUEUE_UPDATE)) अणु
		pr_err("OPAL doesn't support secure variables\n");
		वापस -ENODEV;
	पूर्ण

	set_secvar_ops(&opal_secvar_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id opal_secvar_match[] = अणु
	अणु .compatible = "ibm,secvar-backend",पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver opal_secvar_driver = अणु
	.driver = अणु
		.name = "secvar",
		.of_match_table = opal_secvar_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init opal_secvar_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&opal_secvar_driver, opal_secvar_probe);
पूर्ण
device_initcall(opal_secvar_init);
