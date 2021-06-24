<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is a maximally equidistributed combined Tausworthe generator
 * based on code from GNU Scientअगरic Library 1.5 (30 Jun 2004)
 *
 * lfsr113 version:
 *
 * x_n = (s1_n ^ s2_n ^ s3_n ^ s4_n)
 *
 * s1_अणुn+1पूर्ण = (((s1_n & 4294967294) << 18) ^ (((s1_n <<  6) ^ s1_n) >> 13))
 * s2_अणुn+1पूर्ण = (((s2_n & 4294967288) <<  2) ^ (((s2_n <<  2) ^ s2_n) >> 27))
 * s3_अणुn+1पूर्ण = (((s3_n & 4294967280) <<  7) ^ (((s3_n << 13) ^ s3_n) >> 21))
 * s4_अणुn+1पूर्ण = (((s4_n & 4294967168) << 13) ^ (((s4_n <<  3) ^ s4_n) >> 12))
 *
 * The period of this generator is about 2^113 (see erratum paper).
 *
 * From: P. L'Ecuyer, "Maximally Equidistributed Combined Tausworthe
 * Generators", Mathematics of Computation, 65, 213 (1996), 203--213:
 * http://www.iro.umontreal.ca/~lecuyer/myftp/papers/tausme.ps
 * ftp://ftp.iro.umontreal.ca/pub/simulation/lecuyer/papers/tausme.ps
 *
 * There is an erratum in the paper "Tables of Maximally Equidistributed
 * Combined LFSR Generators", Mathematics of Computation, 68, 225 (1999),
 * 261--269: http://www.iro.umontreal.ca/~lecuyer/myftp/papers/tausme2.ps
 *
 *      ... the k_j most signअगरicant bits of z_j must be non-zero,
 *      क्रम each j. (Note: this restriction also applies to the
 *      computer code given in [4], but was mistakenly not mentioned
 *      in that paper.)
 *
 * This affects the seeding procedure by imposing the requirement
 * s1 > 1, s2 > 7, s3 > 15, s4 > 127.
 */

#समावेश <linux/types.h>
#समावेश <linux/percpu.h>
#समावेश <linux/export.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <trace/events/अक्रमom.h>

/**
 *	pअक्रमom_u32_state - seeded pseuकरो-अक्रमom number generator.
 *	@state: poपूर्णांकer to state काष्ठाure holding seeded state.
 *
 *	This is used क्रम pseuकरो-अक्रमomness with no outside seeding.
 *	For more अक्रमom results, use pअक्रमom_u32().
 */
u32 pअक्रमom_u32_state(काष्ठा rnd_state *state)
अणु
#घोषणा TAUSWORTHE(s, a, b, c, d) ((s & c) << d) ^ (((s << a) ^ s) >> b)
	state->s1 = TAUSWORTHE(state->s1,  6U, 13U, 4294967294U, 18U);
	state->s2 = TAUSWORTHE(state->s2,  2U, 27U, 4294967288U,  2U);
	state->s3 = TAUSWORTHE(state->s3, 13U, 21U, 4294967280U,  7U);
	state->s4 = TAUSWORTHE(state->s4,  3U, 12U, 4294967168U, 13U);

	वापस (state->s1 ^ state->s2 ^ state->s3 ^ state->s4);
पूर्ण
EXPORT_SYMBOL(pअक्रमom_u32_state);

/**
 *	pअक्रमom_bytes_state - get the requested number of pseuकरो-अक्रमom bytes
 *
 *	@state: poपूर्णांकer to state काष्ठाure holding seeded state.
 *	@buf: where to copy the pseuकरो-अक्रमom bytes to
 *	@bytes: the requested number of bytes
 *
 *	This is used क्रम pseuकरो-अक्रमomness with no outside seeding.
 *	For more अक्रमom results, use pअक्रमom_bytes().
 */
व्योम pअक्रमom_bytes_state(काष्ठा rnd_state *state, व्योम *buf, माप_प्रकार bytes)
अणु
	u8 *ptr = buf;

	जबतक (bytes >= माप(u32)) अणु
		put_unaligned(pअक्रमom_u32_state(state), (u32 *) ptr);
		ptr += माप(u32);
		bytes -= माप(u32);
	पूर्ण

	अगर (bytes > 0) अणु
		u32 rem = pअक्रमom_u32_state(state);
		करो अणु
			*ptr++ = (u8) rem;
			bytes--;
			rem >>= BITS_PER_BYTE;
		पूर्ण जबतक (bytes > 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pअक्रमom_bytes_state);

अटल व्योम pअक्रमom_warmup(काष्ठा rnd_state *state)
अणु
	/* Calling RNG ten बार to satisfy recurrence condition */
	pअक्रमom_u32_state(state);
	pअक्रमom_u32_state(state);
	pअक्रमom_u32_state(state);
	pअक्रमom_u32_state(state);
	pअक्रमom_u32_state(state);
	pअक्रमom_u32_state(state);
	pअक्रमom_u32_state(state);
	pअक्रमom_u32_state(state);
	pअक्रमom_u32_state(state);
	pअक्रमom_u32_state(state);
पूर्ण

व्योम pअक्रमom_seed_full_state(काष्ठा rnd_state __percpu *pcpu_state)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा rnd_state *state = per_cpu_ptr(pcpu_state, i);
		u32 seeds[4];

		get_अक्रमom_bytes(&seeds, माप(seeds));
		state->s1 = __seed(seeds[0],   2U);
		state->s2 = __seed(seeds[1],   8U);
		state->s3 = __seed(seeds[2],  16U);
		state->s4 = __seed(seeds[3], 128U);

		pअक्रमom_warmup(state);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pअक्रमom_seed_full_state);

#अगर_घोषित CONFIG_RANDOM32_SELFTEST
अटल काष्ठा pअक्रमom_test1 अणु
	u32 seed;
	u32 result;
पूर्ण test1[] = अणु
	अणु 1U, 3484351685U पूर्ण,
	अणु 2U, 2623130059U पूर्ण,
	अणु 3U, 3125133893U पूर्ण,
	अणु 4U,  984847254U पूर्ण,
पूर्ण;

अटल काष्ठा pअक्रमom_test2 अणु
	u32 seed;
	u32 iteration;
	u32 result;
पूर्ण test2[] = अणु
	/* Test हालs against taus113 from GSL library. */
	अणु  931557656U, 959U, 2975593782U पूर्ण,
	अणु 1339693295U, 876U, 3887776532U पूर्ण,
	अणु 1545556285U, 961U, 1615538833U पूर्ण,
	अणु  601730776U, 723U, 1776162651U पूर्ण,
	अणु 1027516047U, 687U,  511983079U पूर्ण,
	अणु  416526298U, 700U,  916156552U पूर्ण,
	अणु 1395522032U, 652U, 2222063676U पूर्ण,
	अणु  366221443U, 617U, 2992857763U पूर्ण,
	अणु 1539836965U, 714U, 3783265725U पूर्ण,
	अणु  556206671U, 994U,  799626459U पूर्ण,
	अणु  684907218U, 799U,  367789491U पूर्ण,
	अणु 2121230701U, 931U, 2115467001U पूर्ण,
	अणु 1668516451U, 644U, 3620590685U पूर्ण,
	अणु  768046066U, 883U, 2034077390U पूर्ण,
	अणु 1989159136U, 833U, 1195767305U पूर्ण,
	अणु  536585145U, 996U, 3577259204U पूर्ण,
	अणु 1008129373U, 642U, 1478080776U पूर्ण,
	अणु 1740775604U, 939U, 1264980372U पूर्ण,
	अणु 1967883163U, 508U,   10734624U पूर्ण,
	अणु 1923019697U, 730U, 3821419629U पूर्ण,
	अणु  442079932U, 560U, 3440032343U पूर्ण,
	अणु 1961302714U, 845U,  841962572U पूर्ण,
	अणु 2030205964U, 962U, 1325144227U पूर्ण,
	अणु 1160407529U, 507U,  240940858U पूर्ण,
	अणु  635482502U, 779U, 4200489746U पूर्ण,
	अणु 1252788931U, 699U,  867195434U पूर्ण,
	अणु 1961817131U, 719U,  668237657U पूर्ण,
	अणु 1071468216U, 983U,  917876630U पूर्ण,
	अणु 1281848367U, 932U, 1003100039U पूर्ण,
	अणु  582537119U, 780U, 1127273778U पूर्ण,
	अणु 1973672777U, 853U, 1071368872U पूर्ण,
	अणु 1896756996U, 762U, 1127851055U पूर्ण,
	अणु  847917054U, 500U, 1717499075U पूर्ण,
	अणु 1240520510U, 951U, 2849576657U पूर्ण,
	अणु 1685071682U, 567U, 1961810396U पूर्ण,
	अणु 1516232129U, 557U,    3173877U पूर्ण,
	अणु 1208118903U, 612U, 1613145022U पूर्ण,
	अणु 1817269927U, 693U, 4279122573U पूर्ण,
	अणु 1510091701U, 717U,  638191229U पूर्ण,
	अणु  365916850U, 807U,  600424314U पूर्ण,
	अणु  399324359U, 702U, 1803598116U पूर्ण,
	अणु 1318480274U, 779U, 2074237022U पूर्ण,
	अणु  697758115U, 840U, 1483639402U पूर्ण,
	अणु 1696507773U, 840U,  577415447U पूर्ण,
	अणु 2081979121U, 981U, 3041486449U पूर्ण,
	अणु  955646687U, 742U, 3846494357U पूर्ण,
	अणु 1250683506U, 749U,  836419859U पूर्ण,
	अणु  595003102U, 534U,  366794109U पूर्ण,
	अणु   47485338U, 558U, 3521120834U पूर्ण,
	अणु  619433479U, 610U, 3991783875U पूर्ण,
	अणु  704096520U, 518U, 4139493852U पूर्ण,
	अणु 1712224984U, 606U, 2393312003U पूर्ण,
	अणु 1318233152U, 922U, 3880361134U पूर्ण,
	अणु  855572992U, 761U, 1472974787U पूर्ण,
	अणु   64721421U, 703U,  683860550U पूर्ण,
	अणु  678931758U, 840U,  380616043U पूर्ण,
	अणु  692711973U, 778U, 1382361947U पूर्ण,
	अणु  677703619U, 530U, 2826914161U पूर्ण,
	अणु   92393223U, 586U, 1522128471U पूर्ण,
	अणु 1222592920U, 743U, 3466726667U पूर्ण,
	अणु  358288986U, 695U, 1091956998U पूर्ण,
	अणु 1935056945U, 958U,  514864477U पूर्ण,
	अणु  735675993U, 990U, 1294239989U पूर्ण,
	अणु 1560089402U, 897U, 2238551287U पूर्ण,
	अणु   70616361U, 829U,   22483098U पूर्ण,
	अणु  368234700U, 731U, 2913875084U पूर्ण,
	अणु   20221190U, 879U, 1564152970U पूर्ण,
	अणु  539444654U, 682U, 1835141259U पूर्ण,
	अणु 1314987297U, 840U, 1801114136U पूर्ण,
	अणु 2019295544U, 645U, 3286438930U पूर्ण,
	अणु  469023838U, 716U, 1637918202U पूर्ण,
	अणु 1843754496U, 653U, 2562092152U पूर्ण,
	अणु  400672036U, 809U, 4264212785U पूर्ण,
	अणु  404722249U, 965U, 2704116999U पूर्ण,
	अणु  600702209U, 758U,  584979986U पूर्ण,
	अणु  519953954U, 667U, 2574436237U पूर्ण,
	अणु 1658071126U, 694U, 2214569490U पूर्ण,
	अणु  420480037U, 749U, 3430010866U पूर्ण,
	अणु  690103647U, 969U, 3700758083U पूर्ण,
	अणु 1029424799U, 937U, 3787746841U पूर्ण,
	अणु 2012608669U, 506U, 3362628973U पूर्ण,
	अणु 1535432887U, 998U,   42610943U पूर्ण,
	अणु 1330635533U, 857U, 3040806504U पूर्ण,
	अणु 1223800550U, 539U, 3954229517U पूर्ण,
	अणु 1322411537U, 680U, 3223250324U पूर्ण,
	अणु 1877847898U, 945U, 2915147143U पूर्ण,
	अणु 1646356099U, 874U,  965988280U पूर्ण,
	अणु  805687536U, 744U, 4032277920U पूर्ण,
	अणु 1948093210U, 633U, 1346597684U पूर्ण,
	अणु  392609744U, 783U, 1636083295U पूर्ण,
	अणु  690241304U, 770U, 1201031298U पूर्ण,
	अणु 1360302965U, 696U, 1665394461U पूर्ण,
	अणु 1220090946U, 780U, 1316922812U पूर्ण,
	अणु  447092251U, 500U, 3438743375U पूर्ण,
	अणु 1613868791U, 592U,  828546883U पूर्ण,
	अणु  523430951U, 548U, 2552392304U पूर्ण,
	अणु  726692899U, 810U, 1656872867U पूर्ण,
	अणु 1364340021U, 836U, 3710513486U पूर्ण,
	अणु 1986257729U, 931U,  935013962U पूर्ण,
	अणु  407983964U, 921U,  728767059U पूर्ण,
पूर्ण;

अटल u32 __extract_hwseed(व्योम)
अणु
	अचिन्हित पूर्णांक val = 0;

	(व्योम)(arch_get_अक्रमom_seed_पूर्णांक(&val) ||
	       arch_get_अक्रमom_पूर्णांक(&val));

	वापस val;
पूर्ण

अटल व्योम pअक्रमom_seed_early(काष्ठा rnd_state *state, u32 seed,
			       bool mix_with_hwseed)
अणु
#घोषणा LCG(x)	 ((x) * 69069U)	/* super-duper LCG */
#घोषणा HWSEED() (mix_with_hwseed ? __extract_hwseed() : 0)
	state->s1 = __seed(HWSEED() ^ LCG(seed),        2U);
	state->s2 = __seed(HWSEED() ^ LCG(state->s1),   8U);
	state->s3 = __seed(HWSEED() ^ LCG(state->s2),  16U);
	state->s4 = __seed(HWSEED() ^ LCG(state->s3), 128U);
पूर्ण

अटल पूर्णांक __init pअक्रमom_state_selftest(व्योम)
अणु
	पूर्णांक i, j, errors = 0, runs = 0;
	bool error = false;

	क्रम (i = 0; i < ARRAY_SIZE(test1); i++) अणु
		काष्ठा rnd_state state;

		pअक्रमom_seed_early(&state, test1[i].seed, false);
		pअक्रमom_warmup(&state);

		अगर (test1[i].result != pअक्रमom_u32_state(&state))
			error = true;
	पूर्ण

	अगर (error)
		pr_warn("prandom: seed boundary self test failed\n");
	अन्यथा
		pr_info("prandom: seed boundary self test passed\n");

	क्रम (i = 0; i < ARRAY_SIZE(test2); i++) अणु
		काष्ठा rnd_state state;

		pअक्रमom_seed_early(&state, test2[i].seed, false);
		pअक्रमom_warmup(&state);

		क्रम (j = 0; j < test2[i].iteration - 1; j++)
			pअक्रमom_u32_state(&state);

		अगर (test2[i].result != pअक्रमom_u32_state(&state))
			errors++;

		runs++;
		cond_resched();
	पूर्ण

	अगर (errors)
		pr_warn("prandom: %d/%d self tests failed\n", errors, runs);
	अन्यथा
		pr_info("prandom: %d self tests passed\n", runs);
	वापस 0;
पूर्ण
core_initcall(pअक्रमom_state_selftest);
#पूर्ण_अगर

/*
 * The pअक्रमom_u32() implementation is now completely separate from the
 * pअक्रमom_state() functions, which are retained (क्रम now) क्रम compatibility.
 *
 * Because of (ab)use in the networking code क्रम choosing अक्रमom TCP/UDP port
 * numbers, which खोलो DoS possibilities अगर guessable, we want something
 * stronger than a standard PRNG.  But the perक्रमmance requirements of
 * the network code करो not allow robust crypto क्रम this application.
 *
 * So this is a homebrew Junior Spaceman implementation, based on the
 * lowest-latency trustworthy crypto primitive available, SipHash.
 * (The authors of SipHash have not been consulted about this abuse of
 * their work.)
 *
 * Standard SipHash-2-4 uses 2n+4 rounds to hash n words of input to
 * one word of output.  This abbreviated version uses 2 rounds per word
 * of output.
 */

काष्ठा sipअक्रम_state अणु
	अचिन्हित दीर्घ v0;
	अचिन्हित दीर्घ v1;
	अचिन्हित दीर्घ v2;
	अचिन्हित दीर्घ v3;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा sipअक्रम_state, net_अक्रम_state) __latent_entropy;
DEFINE_PER_CPU(अचिन्हित दीर्घ, net_अक्रम_noise);
EXPORT_PER_CPU_SYMBOL(net_अक्रम_noise);

/*
 * This is the core CPRNG function.  As "pseudorandom", this is not used
 * क्रम truly valuable things, just पूर्णांकended to be a PITA to guess.
 * For maximum speed, we करो just two SipHash rounds per word.  This is
 * the same rate as 4 rounds per 64 bits that SipHash normally uses,
 * so hopefully it's reasonably secure.
 *
 * There are two changes from the official SipHash finalization:
 * - We omit some स्थिरants XORed with v2 in the SipHash spec as irrelevant;
 *   they are there only to make the output rounds distinct from the input
 *   rounds, and this application has no input rounds.
 * - Rather than वापसing v0^v1^v2^v3, वापस v1+v3.
 *   If you look at the SipHash round, the last operation on v3 is
 *   "v3 ^= v0", so "v0 ^ v3" just unकरोes that, a waste of समय.
 *   Likewise "v1 ^= v2".  (The rotate of v2 makes a dअगरference, but
 *   it still cancels out half of the bits in v2 क्रम no benefit.)
 *   Second, since the last combining operation was xor, जारी the
 *   pattern of alternating xor/add क्रम a tiny bit of extra non-linearity.
 */
अटल अंतरभूत u32 sipअक्रम_u32(काष्ठा sipअक्रम_state *s)
अणु
	अचिन्हित दीर्घ v0 = s->v0, v1 = s->v1, v2 = s->v2, v3 = s->v3;
	अचिन्हित दीर्घ n = raw_cpu_पढ़ो(net_अक्रम_noise);

	v3 ^= n;
	PRND_SIPROUND(v0, v1, v2, v3);
	PRND_SIPROUND(v0, v1, v2, v3);
	v0 ^= n;
	s->v0 = v0;  s->v1 = v1;  s->v2 = v2;  s->v3 = v3;
	वापस v1 + v3;
पूर्ण


/**
 *	pअक्रमom_u32 - pseuकरो अक्रमom number generator
 *
 *	A 32 bit pseuकरो-अक्रमom number is generated using a fast
 *	algorithm suitable क्रम simulation. This algorithm is NOT
 *	considered safe क्रम cryptographic use.
 */
u32 pअक्रमom_u32(व्योम)
अणु
	काष्ठा sipअक्रम_state *state = get_cpu_ptr(&net_अक्रम_state);
	u32 res = sipअक्रम_u32(state);

	trace_pअक्रमom_u32(res);
	put_cpu_ptr(&net_अक्रम_state);
	वापस res;
पूर्ण
EXPORT_SYMBOL(pअक्रमom_u32);

/**
 *	pअक्रमom_bytes - get the requested number of pseuकरो-अक्रमom bytes
 *	@buf: where to copy the pseuकरो-अक्रमom bytes to
 *	@bytes: the requested number of bytes
 */
व्योम pअक्रमom_bytes(व्योम *buf, माप_प्रकार bytes)
अणु
	काष्ठा sipअक्रम_state *state = get_cpu_ptr(&net_अक्रम_state);
	u8 *ptr = buf;

	जबतक (bytes >= माप(u32)) अणु
		put_unaligned(sipअक्रम_u32(state), (u32 *)ptr);
		ptr += माप(u32);
		bytes -= माप(u32);
	पूर्ण

	अगर (bytes > 0) अणु
		u32 rem = sipअक्रम_u32(state);

		करो अणु
			*ptr++ = (u8)rem;
			rem >>= BITS_PER_BYTE;
		पूर्ण जबतक (--bytes > 0);
	पूर्ण
	put_cpu_ptr(&net_अक्रम_state);
पूर्ण
EXPORT_SYMBOL(pअक्रमom_bytes);

/**
 *	pअक्रमom_seed - add entropy to pseuकरो अक्रमom number generator
 *	@entropy: entropy value
 *
 *	Add some additional seed material to the pअक्रमom pool.
 *	The "entropy" is actually our IP address (the only caller is
 *	the network code), not क्रम unpredictability, but to ensure that
 *	dअगरferent machines are initialized dअगरferently.
 */
व्योम pअक्रमom_seed(u32 entropy)
अणु
	पूर्णांक i;

	add_device_अक्रमomness(&entropy, माप(entropy));

	क्रम_each_possible_cpu(i) अणु
		काष्ठा sipअक्रम_state *state = per_cpu_ptr(&net_अक्रम_state, i);
		अचिन्हित दीर्घ v0 = state->v0, v1 = state->v1;
		अचिन्हित दीर्घ v2 = state->v2, v3 = state->v3;

		करो अणु
			v3 ^= entropy;
			PRND_SIPROUND(v0, v1, v2, v3);
			PRND_SIPROUND(v0, v1, v2, v3);
			v0 ^= entropy;
		पूर्ण जबतक (unlikely(!v0 || !v1 || !v2 || !v3));

		WRITE_ONCE(state->v0, v0);
		WRITE_ONCE(state->v1, v1);
		WRITE_ONCE(state->v2, v2);
		WRITE_ONCE(state->v3, v3);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pअक्रमom_seed);

/*
 *	Generate some initially weak seeding values to allow
 *	the pअक्रमom_u32() engine to be started.
 */
अटल पूर्णांक __init pअक्रमom_init_early(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ v0, v1, v2, v3;

	अगर (!arch_get_अक्रमom_दीर्घ(&v0))
		v0 = jअगरfies;
	अगर (!arch_get_अक्रमom_दीर्घ(&v1))
		v1 = अक्रमom_get_entropy();
	v2 = v0 ^ PRND_K0;
	v3 = v1 ^ PRND_K1;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा sipअक्रम_state *state;

		v3 ^= i;
		PRND_SIPROUND(v0, v1, v2, v3);
		PRND_SIPROUND(v0, v1, v2, v3);
		v0 ^= i;

		state = per_cpu_ptr(&net_अक्रम_state, i);
		state->v0 = v0;  state->v1 = v1;
		state->v2 = v2;  state->v3 = v3;
	पूर्ण

	वापस 0;
पूर्ण
core_initcall(pअक्रमom_init_early);


/* Stronger reseeding when available, and periodically thereafter. */
अटल व्योम pअक्रमom_reseed(काष्ठा समयr_list *unused);

अटल DEFINE_TIMER(seed_समयr, pअक्रमom_reseed);

अटल व्योम pअक्रमom_reseed(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ expires;
	पूर्णांक i;

	/*
	 * Reinitialize each CPU's PRNG with 128 bits of key.
	 * No locking on the CPUs, but then somewhat अक्रमom results are,
	 * well, expected.
	 */
	क्रम_each_possible_cpu(i) अणु
		काष्ठा sipअक्रम_state *state;
		अचिन्हित दीर्घ v0 = get_अक्रमom_दीर्घ(), v2 = v0 ^ PRND_K0;
		अचिन्हित दीर्घ v1 = get_अक्रमom_दीर्घ(), v3 = v1 ^ PRND_K1;
#अगर BITS_PER_LONG == 32
		पूर्णांक j;

		/*
		 * On 32-bit machines, hash in two extra words to
		 * approximate 128-bit key length.  Not that the hash
		 * has that much security, but this prevents a trivial
		 * 64-bit brute क्रमce.
		 */
		क्रम (j = 0; j < 2; j++) अणु
			अचिन्हित दीर्घ m = get_अक्रमom_दीर्घ();

			v3 ^= m;
			PRND_SIPROUND(v0, v1, v2, v3);
			PRND_SIPROUND(v0, v1, v2, v3);
			v0 ^= m;
		पूर्ण
#पूर्ण_अगर
		/*
		 * Probably impossible in practice, but there is a
		 * theoretical risk that a race between this reseeding
		 * and the target CPU writing its state back could
		 * create the all-zero SipHash fixed poपूर्णांक.
		 *
		 * To ensure that never happens, ensure the state
		 * we ग_लिखो contains no zero words.
		 */
		state = per_cpu_ptr(&net_अक्रम_state, i);
		WRITE_ONCE(state->v0, v0 ? v0 : -1ul);
		WRITE_ONCE(state->v1, v1 ? v1 : -1ul);
		WRITE_ONCE(state->v2, v2 ? v2 : -1ul);
		WRITE_ONCE(state->v3, v3 ? v3 : -1ul);
	पूर्ण

	/* reseed every ~60 seconds, in [40 .. 80) पूर्णांकerval with slack */
	expires = round_jअगरfies(jअगरfies + 40 * HZ + pअक्रमom_u32_max(40 * HZ));
	mod_समयr(&seed_समयr, expires);
पूर्ण

/*
 * The अक्रमom पढ़ोy callback can be called from almost any पूर्णांकerrupt.
 * To aव्योम worrying about whether it's safe to delay that पूर्णांकerrupt
 * दीर्घ enough to seed all CPUs, just schedule an immediate समयr event.
 */
अटल व्योम pअक्रमom_समयr_start(काष्ठा अक्रमom_पढ़ोy_callback *unused)
अणु
	mod_समयr(&seed_समयr, jअगरfies);
पूर्ण

#अगर_घोषित CONFIG_RANDOM32_SELFTEST
/* Principle: True 32-bit अक्रमom numbers will all have 16 dअगरfering bits on
 * average. For each 32-bit number, there are 601M numbers dअगरfering by 16
 * bits, and 89% of the numbers dअगरfer by at least 12 bits. Note that more
 * than 16 dअगरfering bits also implies a correlation with inverted bits. Thus
 * we take 1024 अक्रमom numbers and compare each of them to the other ones,
 * counting the deviation of correlated bits to 16. Constants report 32,
 * counters 32-log2(TEST_SIZE), and pure अक्रमoms, around 6 or lower. With the
 * u32 total, TEST_SIZE may be as large as 4096 samples.
 */
#घोषणा TEST_SIZE 1024
अटल पूर्णांक __init pअक्रमom32_state_selftest(व्योम)
अणु
	अचिन्हित पूर्णांक x, y, bits, samples;
	u32 xor, flip;
	u32 total;
	u32 *data;

	data = kदो_स्मृति(माप(*data) * TEST_SIZE, GFP_KERNEL);
	अगर (!data)
		वापस 0;

	क्रम (samples = 0; samples < TEST_SIZE; samples++)
		data[samples] = pअक्रमom_u32();

	flip = total = 0;
	क्रम (x = 0; x < samples; x++) अणु
		क्रम (y = 0; y < samples; y++) अणु
			अगर (x == y)
				जारी;
			xor = data[x] ^ data[y];
			flip |= xor;
			bits = hweight32(xor);
			total += (bits - 16) * (bits - 16);
		पूर्ण
	पूर्ण

	/* We'll वापस the average deviation as 2*वर्ग_मूल(corr/samples), which
	 * is also वर्ग_मूल(4*corr/samples) which provides a better resolution.
	 */
	bits = पूर्णांक_वर्ग_मूल(total / (samples * (samples - 1)) * 4);
	अगर (bits > 6)
		pr_warn("prandom32: self test failed (at least %u bits"
			" correlated, fixed_mask=%#x fixed_value=%#x\n",
			bits, ~flip, data[0] & ~flip);
	अन्यथा
		pr_info("prandom32: self test passed (less than %u bits"
			" correlated)\n",
			bits+1);
	kमुक्त(data);
	वापस 0;
पूर्ण
core_initcall(pअक्रमom32_state_selftest);
#पूर्ण_अगर /*  CONFIG_RANDOM32_SELFTEST */

/*
 * Start periodic full reseeding as soon as strong
 * अक्रमom numbers are available.
 */
अटल पूर्णांक __init pअक्रमom_init_late(व्योम)
अणु
	अटल काष्ठा अक्रमom_पढ़ोy_callback अक्रमom_पढ़ोy = अणु
		.func = pअक्रमom_समयr_start
	पूर्ण;
	पूर्णांक ret = add_अक्रमom_पढ़ोy_callback(&अक्रमom_पढ़ोy);

	अगर (ret == -EALREADY) अणु
		pअक्रमom_समयr_start(&अक्रमom_पढ़ोy);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण
late_initcall(pअक्रमom_init_late);
