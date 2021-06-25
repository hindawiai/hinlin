<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */

#समावेश "pvrusb2-std.h"
#समावेश "pvrusb2-debug.h"
#समावेश <यंत्र/माला.स>
#समावेश <linux/slab.h>

काष्ठा std_name अणु
	स्थिर अक्षर *name;
	v4l2_std_id id;
पूर्ण;


#घोषणा CSTD_PAL \
	(V4L2_STD_PAL_B| \
	 V4L2_STD_PAL_B1| \
	 V4L2_STD_PAL_G| \
	 V4L2_STD_PAL_H| \
	 V4L2_STD_PAL_I| \
	 V4L2_STD_PAL_D| \
	 V4L2_STD_PAL_D1| \
	 V4L2_STD_PAL_K| \
	 V4L2_STD_PAL_M| \
	 V4L2_STD_PAL_N| \
	 V4L2_STD_PAL_Nc| \
	 V4L2_STD_PAL_60)

#घोषणा CSTD_NTSC \
	(V4L2_STD_NTSC_M| \
	 V4L2_STD_NTSC_M_JP| \
	 V4L2_STD_NTSC_M_KR| \
	 V4L2_STD_NTSC_443)

#घोषणा CSTD_ATSC \
	(V4L2_STD_ATSC_8_VSB| \
	 V4L2_STD_ATSC_16_VSB)

#घोषणा CSTD_SECAM \
	(V4L2_STD_SECAM_B| \
	 V4L2_STD_SECAM_D| \
	 V4L2_STD_SECAM_G| \
	 V4L2_STD_SECAM_H| \
	 V4L2_STD_SECAM_K| \
	 V4L2_STD_SECAM_K1| \
	 V4L2_STD_SECAM_L| \
	 V4L2_STD_SECAM_LC)

#घोषणा TSTD_B   (V4L2_STD_PAL_B|V4L2_STD_SECAM_B)
#घोषणा TSTD_B1  (V4L2_STD_PAL_B1)
#घोषणा TSTD_D   (V4L2_STD_PAL_D|V4L2_STD_SECAM_D)
#घोषणा TSTD_D1  (V4L2_STD_PAL_D1)
#घोषणा TSTD_G   (V4L2_STD_PAL_G|V4L2_STD_SECAM_G)
#घोषणा TSTD_H   (V4L2_STD_PAL_H|V4L2_STD_SECAM_H)
#घोषणा TSTD_I   (V4L2_STD_PAL_I)
#घोषणा TSTD_K   (V4L2_STD_PAL_K|V4L2_STD_SECAM_K)
#घोषणा TSTD_K1  (V4L2_STD_SECAM_K1)
#घोषणा TSTD_L   (V4L2_STD_SECAM_L)
#घोषणा TSTD_M   (V4L2_STD_PAL_M|V4L2_STD_NTSC_M)
#घोषणा TSTD_N   (V4L2_STD_PAL_N)
#घोषणा TSTD_Nc  (V4L2_STD_PAL_Nc)
#घोषणा TSTD_60  (V4L2_STD_PAL_60)

#घोषणा CSTD_ALL (CSTD_PAL|CSTD_NTSC|CSTD_ATSC|CSTD_SECAM)

/* Mapping of standard bits to color प्रणाली */
अटल स्थिर काष्ठा std_name std_groups[] = अणु
	अणु"PAL",CSTD_PALपूर्ण,
	अणु"NTSC",CSTD_NTSCपूर्ण,
	अणु"SECAM",CSTD_SECAMपूर्ण,
	अणु"ATSC",CSTD_ATSCपूर्ण,
पूर्ण;

/* Mapping of standard bits to modulation प्रणाली */
अटल स्थिर काष्ठा std_name std_items[] = अणु
	अणु"B",TSTD_Bपूर्ण,
	अणु"B1",TSTD_B1पूर्ण,
	अणु"D",TSTD_Dपूर्ण,
	अणु"D1",TSTD_D1पूर्ण,
	अणु"G",TSTD_Gपूर्ण,
	अणु"H",TSTD_Hपूर्ण,
	अणु"I",TSTD_Iपूर्ण,
	अणु"K",TSTD_Kपूर्ण,
	अणु"K1",TSTD_K1पूर्ण,
	अणु"L",TSTD_Lपूर्ण,
	अणु"LC",V4L2_STD_SECAM_LCपूर्ण,
	अणु"M",TSTD_Mपूर्ण,
	अणु"Mj",V4L2_STD_NTSC_M_JPपूर्ण,
	अणु"443",V4L2_STD_NTSC_443पूर्ण,
	अणु"Mk",V4L2_STD_NTSC_M_KRपूर्ण,
	अणु"N",TSTD_Nपूर्ण,
	अणु"Nc",TSTD_Ncपूर्ण,
	अणु"60",TSTD_60पूर्ण,
	अणु"8VSB",V4L2_STD_ATSC_8_VSBपूर्ण,
	अणु"16VSB",V4L2_STD_ATSC_16_VSBपूर्ण,
पूर्ण;


// Search an array of std_name काष्ठाures and वापस a poपूर्णांकer to the
// element with the matching name.
अटल स्थिर काष्ठा std_name *find_std_name(स्थिर काष्ठा std_name *arrPtr,
					    अचिन्हित पूर्णांक arrSize,
					    स्थिर अक्षर *bufPtr,
					    अचिन्हित पूर्णांक bufSize)
अणु
	अचिन्हित पूर्णांक idx;
	स्थिर काष्ठा std_name *p;
	क्रम (idx = 0; idx < arrSize; idx++) अणु
		p = arrPtr + idx;
		अगर (म_माप(p->name) != bufSize) जारी;
		अगर (!स_भेद(bufPtr,p->name,bufSize)) वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण


पूर्णांक pvr2_std_str_to_id(v4l2_std_id *idPtr,स्थिर अक्षर *bufPtr,
		       अचिन्हित पूर्णांक bufSize)
अणु
	v4l2_std_id id = 0;
	v4l2_std_id cmsk = 0;
	v4l2_std_id t;
	पूर्णांक mMode = 0;
	अचिन्हित पूर्णांक cnt;
	अक्षर ch;
	स्थिर काष्ठा std_name *sp;

	जबतक (bufSize) अणु
		अगर (!mMode) अणु
			cnt = 0;
			जबतक ((cnt < bufSize) && (bufPtr[cnt] != '-')) cnt++;
			अगर (cnt >= bufSize) वापस 0; // No more अक्षरacters
			sp = find_std_name(std_groups, ARRAY_SIZE(std_groups),
					   bufPtr,cnt);
			अगर (!sp) वापस 0; // Illegal color प्रणाली name
			cnt++;
			bufPtr += cnt;
			bufSize -= cnt;
			mMode = !0;
			cmsk = sp->id;
			जारी;
		पूर्ण
		cnt = 0;
		जबतक (cnt < bufSize) अणु
			ch = bufPtr[cnt];
			अगर (ch == ';') अणु
				mMode = 0;
				अवरोध;
			पूर्ण
			अगर (ch == '/') अवरोध;
			cnt++;
		पूर्ण
		sp = find_std_name(std_items, ARRAY_SIZE(std_items),
				   bufPtr,cnt);
		अगर (!sp) वापस 0; // Illegal modulation प्रणाली ID
		t = sp->id & cmsk;
		अगर (!t) वापस 0; // Specअगरic color + modulation प्रणाली illegal
		id |= t;
		अगर (cnt < bufSize) cnt++;
		bufPtr += cnt;
		bufSize -= cnt;
	पूर्ण

	अगर (idPtr) *idPtr = id;
	वापस !0;
पूर्ण


अचिन्हित पूर्णांक pvr2_std_id_to_str(अक्षर *bufPtr, अचिन्हित पूर्णांक bufSize,
				v4l2_std_id id)
अणु
	अचिन्हित पूर्णांक idx1,idx2;
	स्थिर काष्ठा std_name *ip,*gp;
	पूर्णांक gfl,cfl;
	अचिन्हित पूर्णांक c1,c2;
	cfl = 0;
	c1 = 0;
	क्रम (idx1 = 0; idx1 < ARRAY_SIZE(std_groups); idx1++) अणु
		gp = std_groups + idx1;
		gfl = 0;
		क्रम (idx2 = 0; idx2 < ARRAY_SIZE(std_items); idx2++) अणु
			ip = std_items + idx2;
			अगर (!(gp->id & ip->id & id)) जारी;
			अगर (!gfl) अणु
				अगर (cfl) अणु
					c2 = scnम_लिखो(bufPtr,bufSize,";");
					c1 += c2;
					bufSize -= c2;
					bufPtr += c2;
				पूर्ण
				cfl = !0;
				c2 = scnम_लिखो(bufPtr,bufSize,
					       "%s-",gp->name);
				gfl = !0;
			पूर्ण अन्यथा अणु
				c2 = scnम_लिखो(bufPtr,bufSize,"/");
			पूर्ण
			c1 += c2;
			bufSize -= c2;
			bufPtr += c2;
			c2 = scnम_लिखो(bufPtr,bufSize,
				       ip->name);
			c1 += c2;
			bufSize -= c2;
			bufPtr += c2;
		पूर्ण
	पूर्ण
	वापस c1;
पूर्ण


// Template data क्रम possible क्रमागतerated video standards.  Here we group
// standards which share common frame rates and resolution.
अटल काष्ठा v4l2_standard generic_standards[] = अणु
	अणु
		.id             = (TSTD_B|TSTD_B1|
				   TSTD_D|TSTD_D1|
				   TSTD_G|
				   TSTD_H|
				   TSTD_I|
				   TSTD_K|TSTD_K1|
				   TSTD_L|
				   V4L2_STD_SECAM_LC |
				   TSTD_N|TSTD_Nc),
		.frameperiod    =
		अणु
			.numerator  = 1,
			.denominator= 25
		पूर्ण,
		.framelines     = 625,
		.reserved       = अणु0,0,0,0पूर्ण
	पूर्ण, अणु
		.id             = (TSTD_M|
				   V4L2_STD_NTSC_M_JP|
				   V4L2_STD_NTSC_M_KR),
		.frameperiod    =
		अणु
			.numerator  = 1001,
			.denominator= 30000
		पूर्ण,
		.framelines     = 525,
		.reserved       = अणु0,0,0,0पूर्ण
	पूर्ण, अणु // This is a total wild guess
		.id             = (TSTD_60),
		.frameperiod    =
		अणु
			.numerator  = 1001,
			.denominator= 30000
		पूर्ण,
		.framelines     = 525,
		.reserved       = अणु0,0,0,0पूर्ण
	पूर्ण, अणु // This is total wild guess
		.id             = V4L2_STD_NTSC_443,
		.frameperiod    =
		अणु
			.numerator  = 1001,
			.denominator= 30000
		पूर्ण,
		.framelines     = 525,
		.reserved       = अणु0,0,0,0पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा v4l2_standard *match_std(v4l2_std_id id)
अणु
	अचिन्हित पूर्णांक idx;
	क्रम (idx = 0; idx < ARRAY_SIZE(generic_standards); idx++) अणु
		अगर (generic_standards[idx].id & id) अणु
			वापस generic_standards + idx;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक pvr2_std_fill(काष्ठा v4l2_standard *std,v4l2_std_id id)
अणु
	काष्ठा v4l2_standard *ढाँचा;
	पूर्णांक idx;
	अचिन्हित पूर्णांक bcnt;
	ढाँचा = match_std(id);
	अगर (!ढाँचा) वापस 0;
	idx = std->index;
	स_नकल(std,ढाँचा,माप(*ढाँचा));
	std->index = idx;
	std->id = id;
	bcnt = pvr2_std_id_to_str(std->name,माप(std->name)-1,id);
	std->name[bcnt] = 0;
	pvr2_trace(PVR2_TRACE_STD,"Set up standard idx=%u name=%s",
		   std->index,std->name);
	वापस !0;
पूर्ण

/* These are special हालs of combined standards that we should क्रमागतerate
   separately अगर the component pieces are present. */
अटल v4l2_std_id std_mixes[] = अणु
	V4L2_STD_PAL_B | V4L2_STD_PAL_G,
	V4L2_STD_PAL_D | V4L2_STD_PAL_K,
	V4L2_STD_SECAM_B | V4L2_STD_SECAM_G,
	V4L2_STD_SECAM_D | V4L2_STD_SECAM_K,
पूर्ण;

काष्ठा v4l2_standard *pvr2_std_create_क्रमागत(अचिन्हित पूर्णांक *countptr,
					   v4l2_std_id id)
अणु
	अचिन्हित पूर्णांक std_cnt = 0;
	अचिन्हित पूर्णांक idx,bcnt,idx2;
	v4l2_std_id idmsk,cmsk,fmsk;
	काष्ठा v4l2_standard *stddefs;

	अगर (pvrusb2_debug & PVR2_TRACE_STD) अणु
		अक्षर buf[100];
		bcnt = pvr2_std_id_to_str(buf,माप(buf),id);
		pvr2_trace(
			PVR2_TRACE_STD,"Mapping standards mask=0x%x (%.*s)",
			(पूर्णांक)id,bcnt,buf);
	पूर्ण

	*countptr = 0;
	std_cnt = 0;
	fmsk = 0;
	क्रम (idmsk = 1, cmsk = id; cmsk; idmsk <<= 1) अणु
		अगर (!(idmsk & cmsk)) जारी;
		cmsk &= ~idmsk;
		अगर (match_std(idmsk)) अणु
			std_cnt++;
			जारी;
		पूर्ण
		fmsk |= idmsk;
	पूर्ण

	क्रम (idx2 = 0; idx2 < ARRAY_SIZE(std_mixes); idx2++) अणु
		अगर ((id & std_mixes[idx2]) == std_mixes[idx2]) std_cnt++;
	पूर्ण

	/* Don't complain about ATSC standard values */
	fmsk &= ~CSTD_ATSC;

	अगर (fmsk) अणु
		अक्षर buf[100];
		bcnt = pvr2_std_id_to_str(buf,माप(buf),fmsk);
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"***WARNING*** Failed to classify the following standard(s): %.*s",
			bcnt,buf);
	पूर्ण

	pvr2_trace(PVR2_TRACE_STD,"Setting up %u unique standard(s)",
		   std_cnt);
	अगर (!std_cnt) वापस शून्य; // paranoia

	stddefs = kसुस्मृति(std_cnt, माप(काष्ठा v4l2_standard),
			  GFP_KERNEL);
	अगर (!stddefs)
		वापस शून्य;

	क्रम (idx = 0; idx < std_cnt; idx++)
		stddefs[idx].index = idx;

	idx = 0;

	/* Enumerate potential special हालs */
	क्रम (idx2 = 0; (idx2 < ARRAY_SIZE(std_mixes)) && (idx < std_cnt);
	     idx2++) अणु
		अगर (!(id & std_mixes[idx2])) जारी;
		अगर (pvr2_std_fill(stddefs+idx,std_mixes[idx2])) idx++;
	पूर्ण
	/* Now क्रमागतerate inभागidual pieces */
	क्रम (idmsk = 1, cmsk = id; cmsk && (idx < std_cnt); idmsk <<= 1) अणु
		अगर (!(idmsk & cmsk)) जारी;
		cmsk &= ~idmsk;
		अगर (!pvr2_std_fill(stddefs+idx,idmsk)) जारी;
		idx++;
	पूर्ण

	*countptr = std_cnt;
	वापस stddefs;
पूर्ण

v4l2_std_id pvr2_std_get_usable(व्योम)
अणु
	वापस CSTD_ALL;
पूर्ण
