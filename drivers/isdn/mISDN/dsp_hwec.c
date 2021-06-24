<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dsp_hwec.c:
 * builtin mISDN dsp pipeline element क्रम enabling the hw echocanceller
 *
 * Copyright (C) 2007, Nadi Sarrar
 *
 * Nadi Sarrar <nadi@beronet.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/mISDNdsp.h>
#समावेश <linux/mISDNअगर.h>
#समावेश "core.h"
#समावेश "dsp.h"
#समावेश "dsp_hwec.h"

अटल काष्ठा mISDN_dsp_element_arg args[] = अणु
	अणु "deftaps", "128", "Set the number of taps of cancellation." पूर्ण,
पूर्ण;

अटल काष्ठा mISDN_dsp_element dsp_hwec_p = अणु
	.name = "hwec",
	.new = शून्य,
	.मुक्त = शून्य,
	.process_tx = शून्य,
	.process_rx = शून्य,
	.num_args = ARRAY_SIZE(args),
	.args = args,
पूर्ण;
काष्ठा mISDN_dsp_element *dsp_hwec = &dsp_hwec_p;

व्योम dsp_hwec_enable(काष्ठा dsp *dsp, स्थिर अक्षर *arg)
अणु
	पूर्णांक deftaps = 128,
		len;
	काष्ठा mISDN_ctrl_req	cq;

	अगर (!dsp) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to enable hwec: dsp is NULL\n",
		       __func__);
		वापस;
	पूर्ण

	अगर (!arg)
		जाओ _करो;

	len = म_माप(arg);
	अगर (!len)
		जाओ _करो;

	अणु
		अक्षर *dup, *tok, *name, *val;
		पूर्णांक पंचांगp;

		dup = kstrdup(arg, GFP_ATOMIC);
		अगर (!dup)
			वापस;

		जबतक ((tok = strsep(&dup, ","))) अणु
			अगर (!म_माप(tok))
				जारी;
			name = strsep(&tok, "=");
			val = tok;

			अगर (!val)
				जारी;

			अगर (!म_भेद(name, "deftaps")) अणु
				अगर (माला_पूछो(val, "%d", &पंचांगp) == 1)
					deftaps = पंचांगp;
			पूर्ण
		पूर्ण

		kमुक्त(dup);
	पूर्ण

_करो:
	prपूर्णांकk(KERN_DEBUG "%s: enabling hwec with deftaps=%d\n",
	       __func__, deftaps);
	स_रखो(&cq, 0, माप(cq));
	cq.op = MISDN_CTRL_HFC_ECHOCAN_ON;
	cq.p1 = deftaps;
	अगर (!dsp->ch.peer->ctrl(&dsp->ch, CONTROL_CHANNEL, &cq)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: CONTROL_CHANNEL failed\n",
		       __func__);
		वापस;
	पूर्ण
पूर्ण

व्योम dsp_hwec_disable(काष्ठा dsp *dsp)
अणु
	काष्ठा mISDN_ctrl_req	cq;

	अगर (!dsp) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to disable hwec: dsp is NULL\n",
		       __func__);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: disabling hwec\n", __func__);
	स_रखो(&cq, 0, माप(cq));
	cq.op = MISDN_CTRL_HFC_ECHOCAN_OFF;
	अगर (!dsp->ch.peer->ctrl(&dsp->ch, CONTROL_CHANNEL, &cq)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: CONTROL_CHANNEL failed\n",
		       __func__);
		वापस;
	पूर्ण
पूर्ण

पूर्णांक dsp_hwec_init(व्योम)
अणु
	mISDN_dsp_element_रेजिस्टर(dsp_hwec);

	वापस 0;
पूर्ण

व्योम dsp_hwec_निकास(व्योम)
अणु
	mISDN_dsp_element_unरेजिस्टर(dsp_hwec);
पूर्ण
