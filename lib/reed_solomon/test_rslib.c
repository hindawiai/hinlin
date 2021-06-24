<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tests क्रम Generic Reed Solomon encoder / decoder library
 *
 * Written by Ferdinand Blomqvist
 * Based on previous work by Phil Karn, KA9Q
 */
#समावेश <linux/rslib.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>

क्रमागत verbosity अणु
	V_SILENT,
	V_PROGRESS,
	V_CSUMMARY
पूर्ण;

क्रमागत method अणु
	CORR_BUFFER,
	CALLER_SYNDROME,
	IN_PLACE
पूर्ण;

#घोषणा __param(type, name, init, msg)		\
	अटल type name = init;		\
	module_param(name, type, 0444);		\
	MODULE_PARM_DESC(name, msg)

__param(पूर्णांक, v, V_PROGRESS, "Verbosity level");
__param(पूर्णांक, ewsc, 1, "Erasures without symbol corruption");
__param(पूर्णांक, bc, 1, "Test for correct behaviour beyond error correction capacity");

काष्ठा etab अणु
	पूर्णांक	symsize;
	पूर्णांक	genpoly;
	पूर्णांक	fcs;
	पूर्णांक	prim;
	पूर्णांक	nroots;
	पूर्णांक	ntrials;
पूर्ण;

/* List of codes to test */
अटल काष्ठा etab Tab[] = अणु
	अणु2,	0x7,	1,	1,	1,	100000	पूर्ण,
	अणु3,	0xb,	1,	1,	2,	100000	पूर्ण,
	अणु3,	0xb,	1,	1,	3,	100000	पूर्ण,
	अणु3,	0xb,	2,	1,	4,	100000	पूर्ण,
	अणु4,	0x13,	1,	1,	4,	10000	पूर्ण,
	अणु5,	0x25,	1,	1,	6,	1000	पूर्ण,
	अणु6,	0x43,	3,	1,	8,	1000	पूर्ण,
	अणु7,	0x89,	1,	1,	14,	500	पूर्ण,
	अणु8,	0x11d,	1,	1,	30,	100	पूर्ण,
	अणु8,	0x187,	112,	11,	32,	100	पूर्ण,
	अणु9,	0x211,	1,	1,	33,	80	पूर्ण,
	अणु0, 0, 0, 0, 0, 0पूर्ण,
पूर्ण;


काष्ठा estat अणु
	पूर्णांक	dwrong;
	पूर्णांक	irv;
	पूर्णांक	wepos;
	पूर्णांक	nwords;
पूर्ण;

काष्ठा bcstat अणु
	पूर्णांक	rfail;
	पूर्णांक	rsuccess;
	पूर्णांक	noncw;
	पूर्णांक	nwords;
पूर्ण;

काष्ठा wspace अणु
	uपूर्णांक16_t	*c;		/* sent codeword */
	uपूर्णांक16_t	*r;		/* received word */
	uपूर्णांक16_t	*s;		/* syndrome */
	uपूर्णांक16_t	*corr;		/* correction buffer */
	पूर्णांक		*errlocs;
	पूर्णांक		*derrlocs;
पूर्ण;

काष्ठा pad अणु
	पूर्णांक	mult;
	पूर्णांक	shअगरt;
पूर्ण;

अटल काष्ठा pad pad_coef[] = अणु
	अणु 0, 0 पूर्ण,
	अणु 1, 2 पूर्ण,
	अणु 1, 1 पूर्ण,
	अणु 3, 2 पूर्ण,
	अणु 1, 0 पूर्ण,
पूर्ण;

अटल व्योम मुक्त_ws(काष्ठा wspace *ws)
अणु
	अगर (!ws)
		वापस;

	kमुक्त(ws->errlocs);
	kमुक्त(ws->c);
	kमुक्त(ws);
पूर्ण

अटल काष्ठा wspace *alloc_ws(काष्ठा rs_codec *rs)
अणु
	पूर्णांक nroots = rs->nroots;
	काष्ठा wspace *ws;
	पूर्णांक nn = rs->nn;

	ws = kzalloc(माप(*ws), GFP_KERNEL);
	अगर (!ws)
		वापस शून्य;

	ws->c = kदो_स्मृति_array(2 * (nn + nroots),
				माप(uपूर्णांक16_t), GFP_KERNEL);
	अगर (!ws->c)
		जाओ err;

	ws->r = ws->c + nn;
	ws->s = ws->r + nn;
	ws->corr = ws->s + nroots;

	ws->errlocs = kदो_स्मृति_array(nn + nroots, माप(पूर्णांक), GFP_KERNEL);
	अगर (!ws->errlocs)
		जाओ err;

	ws->derrlocs = ws->errlocs + nn;
	वापस ws;

err:
	मुक्त_ws(ws);
	वापस शून्य;
पूर्ण


/*
 * Generates a अक्रमom codeword and stores it in c. Generates अक्रमom errors and
 * erasures, and stores the अक्रमom word with errors in r. Erasure positions are
 * stored in derrlocs, जबतक errlocs has one of three values in every position:
 *
 * 0 अगर there is no error in this position;
 * 1 अगर there is a symbol error in this position;
 * 2 अगर there is an erasure without symbol corruption.
 *
 * Returns the number of corrupted symbols.
 */
अटल पूर्णांक get_rcw_we(काष्ठा rs_control *rs, काष्ठा wspace *ws,
			पूर्णांक len, पूर्णांक errs, पूर्णांक eras)
अणु
	पूर्णांक nroots = rs->codec->nroots;
	पूर्णांक *derrlocs = ws->derrlocs;
	पूर्णांक *errlocs = ws->errlocs;
	पूर्णांक dlen = len - nroots;
	पूर्णांक nn = rs->codec->nn;
	uपूर्णांक16_t *c = ws->c;
	uपूर्णांक16_t *r = ws->r;
	पूर्णांक errval;
	पूर्णांक errloc;
	पूर्णांक i;

	/* Load c with अक्रमom data and encode */
	क्रम (i = 0; i < dlen; i++)
		c[i] = pअक्रमom_u32() & nn;

	स_रखो(c + dlen, 0, nroots * माप(*c));
	encode_rs16(rs, c, dlen, c + dlen, 0);

	/* Make copyand add errors and erasures */
	स_नकल(r, c, len * माप(*r));
	स_रखो(errlocs, 0, len * माप(*errlocs));
	स_रखो(derrlocs, 0, nroots * माप(*derrlocs));

	/* Generating अक्रमom errors */
	क्रम (i = 0; i < errs; i++) अणु
		करो अणु
			/* Error value must be nonzero */
			errval = pअक्रमom_u32() & nn;
		पूर्ण जबतक (errval == 0);

		करो अणु
			/* Must not choose the same location twice */
			errloc = pअक्रमom_u32() % len;
		पूर्ण जबतक (errlocs[errloc] != 0);

		errlocs[errloc] = 1;
		r[errloc] ^= errval;
	पूर्ण

	/* Generating अक्रमom erasures */
	क्रम (i = 0; i < eras; i++) अणु
		करो अणु
			/* Must not choose the same location twice */
			errloc = pअक्रमom_u32() % len;
		पूर्ण जबतक (errlocs[errloc] != 0);

		derrlocs[i] = errloc;

		अगर (ewsc && (pअक्रमom_u32() & 1)) अणु
			/* Erasure with the symbol पूर्णांकact */
			errlocs[errloc] = 2;
		पूर्ण अन्यथा अणु
			/* Erasure with corrupted symbol */
			करो अणु
				/* Error value must be nonzero */
				errval = pअक्रमom_u32() & nn;
			पूर्ण जबतक (errval == 0);

			errlocs[errloc] = 1;
			r[errloc] ^= errval;
			errs++;
		पूर्ण
	पूर्ण

	वापस errs;
पूर्ण

अटल व्योम fix_err(uपूर्णांक16_t *data, पूर्णांक nerrs, uपूर्णांक16_t *corr, पूर्णांक *errlocs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nerrs; i++)
		data[errlocs[i]] ^= corr[i];
पूर्ण

अटल व्योम compute_syndrome(काष्ठा rs_control *rsc, uपूर्णांक16_t *data,
				पूर्णांक len, uपूर्णांक16_t *syn)
अणु
	काष्ठा rs_codec *rs = rsc->codec;
	uपूर्णांक16_t *alpha_to = rs->alpha_to;
	uपूर्णांक16_t *index_of = rs->index_of;
	पूर्णांक nroots = rs->nroots;
	पूर्णांक prim = rs->prim;
	पूर्णांक fcr = rs->fcr;
	पूर्णांक i, j;

	/* Calculating syndrome */
	क्रम (i = 0; i < nroots; i++) अणु
		syn[i] = data[0];
		क्रम (j = 1; j < len; j++) अणु
			अगर (syn[i] == 0) अणु
				syn[i] = data[j];
			पूर्ण अन्यथा अणु
				syn[i] = data[j] ^
					alpha_to[rs_modnn(rs, index_of[syn[i]]
						+ (fcr + i) * prim)];
			पूर्ण
		पूर्ण
	पूर्ण

	/* Convert to index क्रमm */
	क्रम (i = 0; i < nroots; i++)
		syn[i] = rs->index_of[syn[i]];
पूर्ण

/* Test up to error correction capacity */
अटल व्योम test_uc(काष्ठा rs_control *rs, पूर्णांक len, पूर्णांक errs,
		पूर्णांक eras, पूर्णांक trials, काष्ठा estat *stat,
		काष्ठा wspace *ws, पूर्णांक method)
अणु
	पूर्णांक dlen = len - rs->codec->nroots;
	पूर्णांक *derrlocs = ws->derrlocs;
	पूर्णांक *errlocs = ws->errlocs;
	uपूर्णांक16_t *corr = ws->corr;
	uपूर्णांक16_t *c = ws->c;
	uपूर्णांक16_t *r = ws->r;
	uपूर्णांक16_t *s = ws->s;
	पूर्णांक derrs, nerrs;
	पूर्णांक i, j;

	क्रम (j = 0; j < trials; j++) अणु
		nerrs = get_rcw_we(rs, ws, len, errs, eras);

		चयन (method) अणु
		हाल CORR_BUFFER:
			derrs = decode_rs16(rs, r, r + dlen, dlen,
					शून्य, eras, derrlocs, 0, corr);
			fix_err(r, derrs, corr, derrlocs);
			अवरोध;
		हाल CALLER_SYNDROME:
			compute_syndrome(rs, r, len, s);
			derrs = decode_rs16(rs, शून्य, शून्य, dlen,
					s, eras, derrlocs, 0, corr);
			fix_err(r, derrs, corr, derrlocs);
			अवरोध;
		हाल IN_PLACE:
			derrs = decode_rs16(rs, r, r + dlen, dlen,
					शून्य, eras, derrlocs, 0, शून्य);
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		अगर (derrs != nerrs)
			stat->irv++;

		अगर (method != IN_PLACE) अणु
			क्रम (i = 0; i < derrs; i++) अणु
				अगर (errlocs[derrlocs[i]] != 1)
					stat->wepos++;
			पूर्ण
		पूर्ण

		अगर (स_भेद(r, c, len * माप(*r)))
			stat->dwrong++;
	पूर्ण
	stat->nwords += trials;
पूर्ण

अटल पूर्णांक ex_rs_helper(काष्ठा rs_control *rs, काष्ठा wspace *ws,
			पूर्णांक len, पूर्णांक trials, पूर्णांक method)
अणु
	अटल स्थिर अक्षर * स्थिर desc[] = अणु
		"Testing correction buffer interface...",
		"Testing with caller provided syndrome...",
		"Testing in-place interface..."
	पूर्ण;

	काष्ठा estat stat = अणु0, 0, 0, 0पूर्ण;
	पूर्णांक nroots = rs->codec->nroots;
	पूर्णांक errs, eras, retval;

	अगर (v >= V_PROGRESS)
		pr_info("  %s\n", desc[method]);

	क्रम (errs = 0; errs <= nroots / 2; errs++)
		क्रम (eras = 0; eras <= nroots - 2 * errs; eras++)
			test_uc(rs, len, errs, eras, trials, &stat, ws, method);

	अगर (v >= V_CSUMMARY) अणु
		pr_info("    Decodes wrong:        %d / %d\n",
				stat.dwrong, stat.nwords);
		pr_info("    Wrong return value:   %d / %d\n",
				stat.irv, stat.nwords);
		अगर (method != IN_PLACE)
			pr_info("    Wrong error position: %d\n", stat.wepos);
	पूर्ण

	retval = stat.dwrong + stat.wepos + stat.irv;
	अगर (retval && v >= V_PROGRESS)
		pr_warn("    FAIL: %d decoding failures!\n", retval);

	वापस retval;
पूर्ण

अटल पूर्णांक exercise_rs(काष्ठा rs_control *rs, काष्ठा wspace *ws,
		       पूर्णांक len, पूर्णांक trials)
अणु

	पूर्णांक retval = 0;
	पूर्णांक i;

	अगर (v >= V_PROGRESS)
		pr_info("Testing up to error correction capacity...\n");

	क्रम (i = 0; i <= IN_PLACE; i++)
		retval |= ex_rs_helper(rs, ws, len, trials, i);

	वापस retval;
पूर्ण

/* Tests क्रम correct behaviour beyond error correction capacity */
अटल व्योम test_bc(काष्ठा rs_control *rs, पूर्णांक len, पूर्णांक errs,
		पूर्णांक eras, पूर्णांक trials, काष्ठा bcstat *stat,
		काष्ठा wspace *ws)
अणु
	पूर्णांक nroots = rs->codec->nroots;
	पूर्णांक dlen = len - nroots;
	पूर्णांक *derrlocs = ws->derrlocs;
	uपूर्णांक16_t *corr = ws->corr;
	uपूर्णांक16_t *r = ws->r;
	पूर्णांक derrs, j;

	क्रम (j = 0; j < trials; j++) अणु
		get_rcw_we(rs, ws, len, errs, eras);
		derrs = decode_rs16(rs, r, r + dlen, dlen,
				शून्य, eras, derrlocs, 0, corr);
		fix_err(r, derrs, corr, derrlocs);

		अगर (derrs >= 0) अणु
			stat->rsuccess++;

			/*
			 * We check that the वापसed word is actually a
			 * codeword. The obious way to करो this would be to
			 * compute the syndrome, but we करोn't want to replicate
			 * that code here. However, all the codes are in
			 * प्रणालीatic क्रमm, and thereक्रमe we can encode the
			 * वापसed word, and see whether the parity changes or
			 * not.
			 */
			स_रखो(corr, 0, nroots * माप(*corr));
			encode_rs16(rs, r, dlen, corr, 0);

			अगर (स_भेद(r + dlen, corr, nroots * माप(*corr)))
				stat->noncw++;
		पूर्ण अन्यथा अणु
			stat->rfail++;
		पूर्ण
	पूर्ण
	stat->nwords += trials;
पूर्ण

अटल पूर्णांक exercise_rs_bc(काष्ठा rs_control *rs, काष्ठा wspace *ws,
			  पूर्णांक len, पूर्णांक trials)
अणु
	काष्ठा bcstat stat = अणु0, 0, 0, 0पूर्ण;
	पूर्णांक nroots = rs->codec->nroots;
	पूर्णांक errs, eras, cutoff;

	अगर (v >= V_PROGRESS)
		pr_info("Testing beyond error correction capacity...\n");

	क्रम (errs = 1; errs <= nroots; errs++) अणु
		eras = nroots - 2 * errs + 1;
		अगर (eras < 0)
			eras = 0;

		cutoff = nroots <= len - errs ? nroots : len - errs;
		क्रम (; eras <= cutoff; eras++)
			test_bc(rs, len, errs, eras, trials, &stat, ws);
	पूर्ण

	अगर (v >= V_CSUMMARY) अणु
		pr_info("  decoder gives up:        %d / %d\n",
				stat.rfail, stat.nwords);
		pr_info("  decoder returns success: %d / %d\n",
				stat.rsuccess, stat.nwords);
		pr_info("    not a codeword:        %d / %d\n",
				stat.noncw, stat.rsuccess);
	पूर्ण

	अगर (stat.noncw && v >= V_PROGRESS)
		pr_warn("    FAIL: %d silent failures!\n", stat.noncw);

	वापस stat.noncw;
पूर्ण

अटल पूर्णांक run_exercise(काष्ठा etab *e)
अणु
	पूर्णांक nn = (1 << e->symsize) - 1;
	पूर्णांक kk = nn - e->nroots;
	काष्ठा rs_control *rsc;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक max_pad = kk - 1;
	पूर्णांक prev_pad = -1;
	काष्ठा wspace *ws;
	पूर्णांक i;

	rsc = init_rs(e->symsize, e->genpoly, e->fcs, e->prim, e->nroots);
	अगर (!rsc)
		वापस retval;

	ws = alloc_ws(rsc->codec);
	अगर (!ws)
		जाओ err;

	retval = 0;
	क्रम (i = 0; i < ARRAY_SIZE(pad_coef); i++) अणु
		पूर्णांक pad = (pad_coef[i].mult * max_pad) >> pad_coef[i].shअगरt;
		पूर्णांक len = nn - pad;

		अगर (pad == prev_pad)
			जारी;

		prev_pad = pad;
		अगर (v >= V_PROGRESS) अणु
			pr_info("Testing (%d,%d)_%d code...\n",
					len, kk - pad, nn + 1);
		पूर्ण

		retval |= exercise_rs(rsc, ws, len, e->ntrials);
		अगर (bc)
			retval |= exercise_rs_bc(rsc, ws, len, e->ntrials);
	पूर्ण

	मुक्त_ws(ws);

err:
	मुक्त_rs(rsc);
	वापस retval;
पूर्ण

अटल पूर्णांक __init test_rslib_init(व्योम)
अणु
	पूर्णांक i, fail = 0;

	क्रम (i = 0; Tab[i].symsize != 0 ; i++) अणु
		पूर्णांक retval;

		retval = run_exercise(Tab + i);
		अगर (retval < 0)
			वापस -ENOMEM;

		fail |= retval;
	पूर्ण

	अगर (fail)
		pr_warn("rslib: test failed\n");
	अन्यथा
		pr_info("rslib: test ok\n");

	वापस -EAGAIN; /* Fail will directly unload the module */
पूर्ण

अटल व्योम __निकास test_rslib_निकास(व्योम)
अणु
पूर्ण

module_init(test_rslib_init)
module_निकास(test_rslib_निकास)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ferdinand Blomqvist");
MODULE_DESCRIPTION("Reed-Solomon library test");
