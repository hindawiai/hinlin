<शैली गुरु>
/*
 *  Copyright (C) 2001 Andrea Arcangeli <andrea@suse.de> SuSE
 *  Copyright 2003 Andi Kleen, SuSE Lअसल.
 *
 *  Thanks to hpa@transmeta.com क्रम some useful hपूर्णांक.
 *  Special thanks to Ingo Molnar क्रम his early experience with
 *  a dअगरferent vsyscall implementation क्रम Linux/IA32 and क्रम the name.
 */

#समावेश <linux/समय.स>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>

#समावेश <यंत्र/vvar.h>

व्योम update_vsyscall_tz(व्योम)
अणु
	अगर (unlikely(vvar_data == शून्य))
		वापस;

	vvar_data->tz_minuteswest = sys_tz.tz_minuteswest;
	vvar_data->tz_dstसमय = sys_tz.tz_dstसमय;
पूर्ण

व्योम update_vsyscall(काष्ठा समयkeeper *tk)
अणु
	काष्ठा vvar_data *vdata = vvar_data;

	अगर (unlikely(vdata == शून्य))
		वापस;

	vvar_ग_लिखो_begin(vdata);
	vdata->vघड़ी_mode = tk->tkr_mono.घड़ी->archdata.vघड़ी_mode;
	vdata->घड़ी.cycle_last = tk->tkr_mono.cycle_last;
	vdata->घड़ी.mask = tk->tkr_mono.mask;
	vdata->घड़ी.mult = tk->tkr_mono.mult;
	vdata->घड़ी.shअगरt = tk->tkr_mono.shअगरt;

	vdata->wall_समय_sec = tk->xसमय_sec;
	vdata->wall_समय_snsec = tk->tkr_mono.xसमय_nsec;

	vdata->monotonic_समय_sec = tk->xसमय_sec +
				    tk->wall_to_monotonic.tv_sec;
	vdata->monotonic_समय_snsec = tk->tkr_mono.xसमय_nsec +
				      (tk->wall_to_monotonic.tv_nsec <<
				       tk->tkr_mono.shअगरt);

	जबतक (vdata->monotonic_समय_snsec >=
	       (((u64)NSEC_PER_SEC) << tk->tkr_mono.shअगरt)) अणु
		vdata->monotonic_समय_snsec -=
				((u64)NSEC_PER_SEC) << tk->tkr_mono.shअगरt;
		vdata->monotonic_समय_sec++;
	पूर्ण

	vdata->wall_समय_coarse_sec = tk->xसमय_sec;
	vdata->wall_समय_coarse_nsec =
			(दीर्घ)(tk->tkr_mono.xसमय_nsec >> tk->tkr_mono.shअगरt);

	vdata->monotonic_समय_coarse_sec =
		vdata->wall_समय_coarse_sec + tk->wall_to_monotonic.tv_sec;
	vdata->monotonic_समय_coarse_nsec =
		vdata->wall_समय_coarse_nsec + tk->wall_to_monotonic.tv_nsec;

	जबतक (vdata->monotonic_समय_coarse_nsec >= NSEC_PER_SEC) अणु
		vdata->monotonic_समय_coarse_nsec -= NSEC_PER_SEC;
		vdata->monotonic_समय_coarse_sec++;
	पूर्ण

	vvar_ग_लिखो_end(vdata);
पूर्ण
