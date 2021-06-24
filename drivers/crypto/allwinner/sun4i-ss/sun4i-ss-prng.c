<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#समावेश "sun4i-ss.h"

पूर्णांक sun4i_ss_prng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed,
		       अचिन्हित पूर्णांक slen)
अणु
	काष्ठा sun4i_ss_alg_ढाँचा *algt;
	काष्ठा rng_alg *alg = crypto_rng_alg(tfm);

	algt = container_of(alg, काष्ठा sun4i_ss_alg_ढाँचा, alg.rng);
	स_नकल(algt->ss->seed, seed, slen);

	वापस 0;
पूर्ण

पूर्णांक sun4i_ss_prng_generate(काष्ठा crypto_rng *tfm, स्थिर u8 *src,
			   अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा sun4i_ss_alg_ढाँचा *algt;
	काष्ठा rng_alg *alg = crypto_rng_alg(tfm);
	पूर्णांक i, err;
	u32 v;
	u32 *data = (u32 *)dst;
	स्थिर u32 mode = SS_OP_PRNG | SS_PRNG_CONTINUE | SS_ENABLED;
	माप_प्रकार len;
	काष्ठा sun4i_ss_ctx *ss;
	अचिन्हित पूर्णांक toकरो = (dlen / 4) * 4;

	algt = container_of(alg, काष्ठा sun4i_ss_alg_ढाँचा, alg.rng);
	ss = algt->ss;

	err = pm_runसमय_resume_and_get(ss->dev);
	अगर (err < 0)
		वापस err;

	अगर (IS_ENABLED(CONFIG_CRYPTO_DEV_SUN4I_SS_DEBUG)) अणु
		algt->stat_req++;
		algt->stat_bytes += toकरो;
	पूर्ण

	spin_lock_bh(&ss->slock);

	ग_लिखोl(mode, ss->base + SS_CTL);

	जबतक (toकरो > 0) अणु
		/* ग_लिखो the seed */
		क्रम (i = 0; i < SS_SEED_LEN / BITS_PER_LONG; i++)
			ग_लिखोl(ss->seed[i], ss->base + SS_KEY0 + i * 4);

		/* Read the अक्रमom data */
		len = min_t(माप_प्रकार, SS_DATA_LEN / BITS_PER_BYTE, toकरो);
		पढ़ोsl(ss->base + SS_TXFIFO, data, len / 4);
		data += len / 4;
		toकरो -= len;

		/* Update the seed */
		क्रम (i = 0; i < SS_SEED_LEN / BITS_PER_LONG; i++) अणु
			v = पढ़ोl(ss->base + SS_KEY0 + i * 4);
			ss->seed[i] = v;
		पूर्ण
	पूर्ण

	ग_लिखोl(0, ss->base + SS_CTL);
	spin_unlock_bh(&ss->slock);

	pm_runसमय_put(ss->dev);

	वापस 0;
पूर्ण
