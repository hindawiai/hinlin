<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Scatterlist Cryptographic API.
 *
 * Procfs inक्रमmation.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2005 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/init.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>	/* क्रम module_name() */
#समावेश <linux/rwsem.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश "internal.h"

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	करोwn_पढ़ो(&crypto_alg_sem);
	वापस seq_list_start(&crypto_alg_list, *pos);
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	वापस seq_list_next(p, &crypto_alg_list, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	up_पढ़ो(&crypto_alg_sem);
पूर्ण

अटल पूर्णांक c_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा crypto_alg *alg = list_entry(p, काष्ठा crypto_alg, cra_list);

	seq_म_लिखो(m, "name         : %s\n", alg->cra_name);
	seq_म_लिखो(m, "driver       : %s\n", alg->cra_driver_name);
	seq_म_लिखो(m, "module       : %s\n", module_name(alg->cra_module));
	seq_म_लिखो(m, "priority     : %d\n", alg->cra_priority);
	seq_म_लिखो(m, "refcnt       : %u\n", refcount_पढ़ो(&alg->cra_refcnt));
	seq_म_लिखो(m, "selftest     : %s\n",
		   (alg->cra_flags & CRYPTO_ALG_TESTED) ?
		   "passed" : "unknown");
	seq_म_लिखो(m, "internal     : %s\n",
		   (alg->cra_flags & CRYPTO_ALG_INTERNAL) ?
		   "yes" : "no");

	अगर (alg->cra_flags & CRYPTO_ALG_LARVAL) अणु
		seq_म_लिखो(m, "type         : larval\n");
		seq_म_लिखो(m, "flags        : 0x%x\n", alg->cra_flags);
		जाओ out;
	पूर्ण

	अगर (alg->cra_type && alg->cra_type->show) अणु
		alg->cra_type->show(m, alg);
		जाओ out;
	पूर्ण

	चयन (alg->cra_flags & CRYPTO_ALG_TYPE_MASK) अणु
	हाल CRYPTO_ALG_TYPE_CIPHER:
		seq_म_लिखो(m, "type         : cipher\n");
		seq_म_लिखो(m, "blocksize    : %u\n", alg->cra_blocksize);
		seq_म_लिखो(m, "min keysize  : %u\n",
					alg->cra_cipher.cia_min_keysize);
		seq_म_लिखो(m, "max keysize  : %u\n",
					alg->cra_cipher.cia_max_keysize);
		अवरोध;
	हाल CRYPTO_ALG_TYPE_COMPRESS:
		seq_म_लिखो(m, "type         : compression\n");
		अवरोध;
	शेष:
		seq_म_लिखो(m, "type         : unknown\n");
		अवरोध;
	पूर्ण

out:
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations crypto_seq_ops = अणु
	.start		= c_start,
	.next		= c_next,
	.stop		= c_stop,
	.show		= c_show
पूर्ण;

व्योम __init crypto_init_proc(व्योम)
अणु
	proc_create_seq("crypto", 0, शून्य, &crypto_seq_ops);
पूर्ण

व्योम __निकास crypto_निकास_proc(व्योम)
अणु
	हटाओ_proc_entry("crypto", शून्य);
पूर्ण
