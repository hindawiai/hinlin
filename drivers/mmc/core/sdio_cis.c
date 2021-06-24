<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/mmc/core/sdio_cis.c
 *
 * Author:	Nicolas Pitre
 * Created:	June 11, 2007
 * Copyright:	MontaVista Software Inc.
 *
 * Copyright 2007 Pierre Ossman
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sdio_func.h>

#समावेश "sdio_cis.h"
#समावेश "sdio_ops.h"

#घोषणा SDIO_READ_CIS_TIMEOUT_MS  (10 * 1000) /* 10s */

अटल पूर्णांक cistpl_vers_1(काष्ठा mmc_card *card, काष्ठा sdio_func *func,
			 स्थिर अचिन्हित अक्षर *buf, अचिन्हित size)
अणु
	u8 major_rev, minor_rev;
	अचिन्हित i, nr_strings;
	अक्षर **buffer, *string;

	अगर (size < 2)
		वापस 0;

	major_rev = buf[0];
	minor_rev = buf[1];

	/* Find all null-terminated (including zero length) strings in
	   the TPLLV1_INFO field. Trailing garbage is ignored. */
	buf += 2;
	size -= 2;

	nr_strings = 0;
	क्रम (i = 0; i < size; i++) अणु
		अगर (buf[i] == 0xff)
			अवरोध;
		अगर (buf[i] == 0)
			nr_strings++;
	पूर्ण
	अगर (nr_strings == 0)
		वापस 0;

	size = i;

	buffer = kzalloc(माप(अक्षर*) * nr_strings + size, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	string = (अक्षर*)(buffer + nr_strings);

	क्रम (i = 0; i < nr_strings; i++) अणु
		buffer[i] = string;
		म_नकल(string, buf);
		string += म_माप(string) + 1;
		buf += म_माप(buf) + 1;
	पूर्ण

	अगर (func) अणु
		func->major_rev = major_rev;
		func->minor_rev = minor_rev;
		func->num_info = nr_strings;
		func->info = (स्थिर अक्षर**)buffer;
	पूर्ण अन्यथा अणु
		card->major_rev = major_rev;
		card->minor_rev = minor_rev;
		card->num_info = nr_strings;
		card->info = (स्थिर अक्षर**)buffer;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cistpl_manfid(काष्ठा mmc_card *card, काष्ठा sdio_func *func,
			 स्थिर अचिन्हित अक्षर *buf, अचिन्हित size)
अणु
	अचिन्हित पूर्णांक venकरोr, device;

	/* TPLMID_MANF */
	venकरोr = buf[0] | (buf[1] << 8);

	/* TPLMID_CARD */
	device = buf[2] | (buf[3] << 8);

	अगर (func) अणु
		func->venकरोr = venकरोr;
		func->device = device;
	पूर्ण अन्यथा अणु
		card->cis.venकरोr = venकरोr;
		card->cis.device = device;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित अक्षर speed_val[16] =
	अणु 0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक speed_unit[8] =
	अणु 10000, 100000, 1000000, 10000000, 0, 0, 0, 0 पूर्ण;


प्रकार पूर्णांक (tpl_parse_t)(काष्ठा mmc_card *, काष्ठा sdio_func *,
			   स्थिर अचिन्हित अक्षर *, अचिन्हित);

काष्ठा cis_tpl अणु
	अचिन्हित अक्षर code;
	अचिन्हित अक्षर min_size;
	tpl_parse_t *parse;
पूर्ण;

अटल पूर्णांक cis_tpl_parse(काष्ठा mmc_card *card, काष्ठा sdio_func *func,
			 स्थिर अक्षर *tpl_descr,
			 स्थिर काष्ठा cis_tpl *tpl, पूर्णांक tpl_count,
			 अचिन्हित अक्षर code,
			 स्थिर अचिन्हित अक्षर *buf, अचिन्हित size)
अणु
	पूर्णांक i, ret;

	/* look क्रम a matching code in the table */
	क्रम (i = 0; i < tpl_count; i++, tpl++) अणु
		अगर (tpl->code == code)
			अवरोध;
	पूर्ण
	अगर (i < tpl_count) अणु
		अगर (size >= tpl->min_size) अणु
			अगर (tpl->parse)
				ret = tpl->parse(card, func, buf, size);
			अन्यथा
				ret = -EILSEQ;	/* known tuple, not parsed */
		पूर्ण अन्यथा अणु
			/* invalid tuple */
			ret = -EINVAL;
		पूर्ण
		अगर (ret && ret != -EILSEQ && ret != -ENOENT) अणु
			pr_err("%s: bad %s tuple 0x%02x (%u bytes)\n",
			       mmc_hostname(card->host), tpl_descr, code, size);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* unknown tuple */
		ret = -ENOENT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cistpl_funce_common(काष्ठा mmc_card *card, काष्ठा sdio_func *func,
			       स्थिर अचिन्हित अक्षर *buf, अचिन्हित size)
अणु
	/* Only valid क्रम the common CIS (function 0) */
	अगर (func)
		वापस -EINVAL;

	/* TPLFE_FN0_BLK_SIZE */
	card->cis.blksize = buf[1] | (buf[2] << 8);

	/* TPLFE_MAX_TRAN_SPEED */
	card->cis.max_dtr = speed_val[(buf[3] >> 3) & 15] *
			    speed_unit[buf[3] & 7];

	वापस 0;
पूर्ण

अटल पूर्णांक cistpl_funce_func(काष्ठा mmc_card *card, काष्ठा sdio_func *func,
			     स्थिर अचिन्हित अक्षर *buf, अचिन्हित size)
अणु
	अचिन्हित vsn;
	अचिन्हित min_size;

	/* Only valid क्रम the inभागidual function's CIS (1-7) */
	अगर (!func)
		वापस -EINVAL;

	/*
	 * This tuple has a dअगरferent length depending on the SDIO spec
	 * version.
	 */
	vsn = func->card->cccr.sdio_vsn;
	min_size = (vsn == SDIO_SDIO_REV_1_00) ? 28 : 42;

	अगर (size == 28 && vsn == SDIO_SDIO_REV_1_10) अणु
		pr_warn("%s: card has broken SDIO 1.1 CIS, forcing SDIO 1.0\n",
			mmc_hostname(card->host));
		vsn = SDIO_SDIO_REV_1_00;
	पूर्ण अन्यथा अगर (size < min_size) अणु
		वापस -EINVAL;
	पूर्ण

	/* TPLFE_MAX_BLK_SIZE */
	func->max_blksize = buf[12] | (buf[13] << 8);

	/* TPLFE_ENABLE_TIMEOUT_VAL, present in ver 1.1 and above */
	अगर (vsn > SDIO_SDIO_REV_1_00)
		func->enable_समयout = (buf[28] | (buf[29] << 8)) * 10;
	अन्यथा
		func->enable_समयout = jअगरfies_to_msecs(HZ);

	वापस 0;
पूर्ण

/*
 * Known TPLFE_TYPEs table क्रम CISTPL_FUNCE tuples.
 *
 * Note that, unlike PCMCIA, CISTPL_FUNCE tuples are not parsed depending
 * on the TPLFID_FUNCTION value of the previous CISTPL_FUNCID as on SDIO
 * TPLFID_FUNCTION is always hardcoded to 0x0C.
 */
अटल स्थिर काष्ठा cis_tpl cis_tpl_funce_list[] = अणु
	अणु	0x00,	4,	cistpl_funce_common		पूर्ण,
	अणु	0x01,	0,	cistpl_funce_func		पूर्ण,
	अणु	0x04,	1+1+6,	/* CISTPL_FUNCE_LAN_NODE_ID */	पूर्ण,
पूर्ण;

अटल पूर्णांक cistpl_funce(काष्ठा mmc_card *card, काष्ठा sdio_func *func,
			स्थिर अचिन्हित अक्षर *buf, अचिन्हित size)
अणु
	अगर (size < 1)
		वापस -EINVAL;

	वापस cis_tpl_parse(card, func, "CISTPL_FUNCE",
			     cis_tpl_funce_list,
			     ARRAY_SIZE(cis_tpl_funce_list),
			     buf[0], buf, size);
पूर्ण

/* Known TPL_CODEs table क्रम CIS tuples */
अटल स्थिर काष्ठा cis_tpl cis_tpl_list[] = अणु
	अणु	0x15,	3,	cistpl_vers_1		पूर्ण,
	अणु	0x20,	4,	cistpl_manfid		पूर्ण,
	अणु	0x21,	2,	/* cistpl_funcid */	पूर्ण,
	अणु	0x22,	0,	cistpl_funce		पूर्ण,
	अणु	0x91,	2,	/* cistpl_sdio_std */	पूर्ण,
पूर्ण;

अटल पूर्णांक sdio_पढ़ो_cis(काष्ठा mmc_card *card, काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;
	काष्ठा sdio_func_tuple *this, **prev;
	अचिन्हित i, ptr = 0;

	/*
	 * Note that this works क्रम the common CIS (function number 0) as
	 * well as a function's CIS * since SDIO_CCCR_CIS and SDIO_FBR_CIS
	 * have the same offset.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		अचिन्हित अक्षर x, fn;

		अगर (func)
			fn = func->num;
		अन्यथा
			fn = 0;

		ret = mmc_io_rw_direct(card, 0, 0,
			SDIO_FBR_BASE(fn) + SDIO_FBR_CIS + i, 0, &x);
		अगर (ret)
			वापस ret;
		ptr |= x << (i * 8);
	पूर्ण

	अगर (func)
		prev = &func->tuples;
	अन्यथा
		prev = &card->tuples;

	अगर (*prev)
		वापस -EINVAL;

	करो अणु
		अचिन्हित अक्षर tpl_code, tpl_link;
		अचिन्हित दीर्घ समयout = jअगरfies +
			msecs_to_jअगरfies(SDIO_READ_CIS_TIMEOUT_MS);

		ret = mmc_io_rw_direct(card, 0, 0, ptr++, 0, &tpl_code);
		अगर (ret)
			अवरोध;

		/* 0xff means we're करोne */
		अगर (tpl_code == 0xff)
			अवरोध;

		/* null entries have no link field or data */
		अगर (tpl_code == 0x00)
			जारी;

		ret = mmc_io_rw_direct(card, 0, 0, ptr++, 0, &tpl_link);
		अगर (ret)
			अवरोध;

		/* a size of 0xff also means we're करोne */
		अगर (tpl_link == 0xff)
			अवरोध;

		this = kदो_स्मृति(माप(*this) + tpl_link, GFP_KERNEL);
		अगर (!this)
			वापस -ENOMEM;

		क्रम (i = 0; i < tpl_link; i++) अणु
			ret = mmc_io_rw_direct(card, 0, 0,
					       ptr + i, 0, &this->data[i]);
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (ret) अणु
			kमुक्त(this);
			अवरोध;
		पूर्ण

		/* Try to parse the CIS tuple */
		ret = cis_tpl_parse(card, func, "CIS",
				    cis_tpl_list, ARRAY_SIZE(cis_tpl_list),
				    tpl_code, this->data, tpl_link);
		अगर (ret == -EILSEQ || ret == -ENOENT) अणु
			/*
			 * The tuple is unknown or known but not parsed.
			 * Queue the tuple क्रम the function driver.
			 */
			this->next = शून्य;
			this->code = tpl_code;
			this->size = tpl_link;
			*prev = this;
			prev = &this->next;

			अगर (ret == -ENOENT) अणु
				अगर (समय_after(jअगरfies, समयout))
					अवरोध;
				/* warn about unknown tuples */
				pr_warn_ratelimited("%s: queuing unknown"
				       " CIS tuple 0x%02x (%u bytes)\n",
				       mmc_hostname(card->host),
				       tpl_code, tpl_link);
			पूर्ण

			/* keep on analyzing tuples */
			ret = 0;
		पूर्ण अन्यथा अणु
			/*
			 * We करोn't need the tuple anymore अगर it was
			 * successfully parsed by the SDIO core or अगर it is
			 * not going to be queued क्रम a driver.
			 */
			kमुक्त(this);
		पूर्ण

		ptr += tpl_link;
	पूर्ण जबतक (!ret);

	/*
	 * Link in all unknown tuples found in the common CIS so that
	 * drivers करोn't have to go digging in two places.
	 */
	अगर (func)
		*prev = card->tuples;

	वापस ret;
पूर्ण

पूर्णांक sdio_पढ़ो_common_cis(काष्ठा mmc_card *card)
अणु
	वापस sdio_पढ़ो_cis(card, शून्य);
पूर्ण

व्योम sdio_मुक्त_common_cis(काष्ठा mmc_card *card)
अणु
	काष्ठा sdio_func_tuple *tuple, *victim;

	tuple = card->tuples;

	जबतक (tuple) अणु
		victim = tuple;
		tuple = tuple->next;
		kमुक्त(victim);
	पूर्ण

	card->tuples = शून्य;
पूर्ण

पूर्णांक sdio_पढ़ो_func_cis(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;

	ret = sdio_पढ़ो_cis(func->card, func);
	अगर (ret)
		वापस ret;

	/*
	 * Since we've linked to tuples in the card काष्ठाure,
	 * we must make sure we have a reference to it.
	 */
	get_device(&func->card->dev);

	/*
	 * Venकरोr/device id is optional क्रम function CIS, so
	 * copy it from the card काष्ठाure as needed.
	 */
	अगर (func->venकरोr == 0) अणु
		func->venकरोr = func->card->cis.venकरोr;
		func->device = func->card->cis.device;
	पूर्ण

	वापस 0;
पूर्ण

व्योम sdio_मुक्त_func_cis(काष्ठा sdio_func *func)
अणु
	काष्ठा sdio_func_tuple *tuple, *victim;

	tuple = func->tuples;

	जबतक (tuple && tuple != func->card->tuples) अणु
		victim = tuple;
		tuple = tuple->next;
		kमुक्त(victim);
	पूर्ण

	func->tuples = शून्य;

	/*
	 * We have now हटाओd the link to the tuples in the
	 * card काष्ठाure, so हटाओ the reference.
	 */
	put_device(&func->card->dev);
पूर्ण

