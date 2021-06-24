<शैली गुरु>
/*
 * Copyright (C) 2003 Jana Saout <jana@saout.de>
 *
 * This file is released under the GPL.
 */

#समावेश <linux/device-mapper.h>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bपन.स>

#घोषणा DM_MSG_PREFIX "zero"

/*
 * Conकाष्ठा a dummy mapping that only वापसs zeros
 */
अटल पूर्णांक zero_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	अगर (argc != 0) अणु
		ti->error = "No arguments required";
		वापस -EINVAL;
	पूर्ण

	/*
	 * Silently drop discards, aव्योमing -EOPNOTSUPP.
	 */
	ti->num_discard_bios = 1;

	वापस 0;
पूर्ण

/*
 * Return zeros only on पढ़ोs
 */
अटल पूर्णांक zero_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	चयन (bio_op(bio)) अणु
	हाल REQ_OP_READ:
		अगर (bio->bi_opf & REQ_RAHEAD) अणु
			/* पढ़ोahead of null bytes only wastes buffer cache */
			वापस DM_MAPIO_KILL;
		पूर्ण
		zero_fill_bio(bio);
		अवरोध;
	हाल REQ_OP_WRITE:
		/* ग_लिखोs get silently dropped */
		अवरोध;
	शेष:
		वापस DM_MAPIO_KILL;
	पूर्ण

	bio_endio(bio);

	/* accepted bio, करोn't make new request */
	वापस DM_MAPIO_SUBMITTED;
पूर्ण

अटल काष्ठा target_type zero_target = अणु
	.name   = "zero",
	.version = अणु1, 1, 0पूर्ण,
	.features = DM_TARGET_NOWAIT,
	.module = THIS_MODULE,
	.ctr    = zero_ctr,
	.map    = zero_map,
पूर्ण;

अटल पूर्णांक __init dm_zero_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_target(&zero_target);

	अगर (r < 0)
		DMERR("register failed %d", r);

	वापस r;
पूर्ण

अटल व्योम __निकास dm_zero_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&zero_target);
पूर्ण

module_init(dm_zero_init)
module_निकास(dm_zero_निकास)

MODULE_AUTHOR("Jana Saout <jana@saout.de>");
MODULE_DESCRIPTION(DM_NAME " dummy target returning zeros");
MODULE_LICENSE("GPL");
