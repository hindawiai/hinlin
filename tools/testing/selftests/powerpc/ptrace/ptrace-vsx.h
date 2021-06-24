<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#घोषणा VEC_MAX 128
#घोषणा VSX_MAX 32
#घोषणा VMX_MAX 32

/*
 * अचिन्हित दीर्घ vsx[32]
 * अचिन्हित दीर्घ load[128]
 */
पूर्णांक validate_vsx(अचिन्हित दीर्घ *vsx, अचिन्हित दीर्घ *load)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VSX_MAX; i++) अणु
		अगर (vsx[i] != load[2 * i + 1]) अणु
			म_लिखो("vsx[%d]: %lx load[%d] %lx\n",
					i, vsx[i], 2 * i + 1, load[2 * i + 1]);
			वापस TEST_FAIL;
		पूर्ण
	पूर्ण
	वापस TEST_PASS;
पूर्ण

/*
 * अचिन्हित दीर्घ vmx[32][2]
 * अचिन्हित दीर्घ load[128]
 */
पूर्णांक validate_vmx(अचिन्हित दीर्घ vmx[][2], अचिन्हित दीर्घ *load)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VMX_MAX; i++) अणु
		#अगर __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		अगर ((vmx[i][0] != load[64 + 2 * i]) ||
				(vmx[i][1] != load[65 + 2 * i])) अणु
			म_लिखो("vmx[%d][0]: %lx load[%d] %lx\n",
					i, vmx[i][0], 64 + 2 * i,
					load[64 + 2 * i]);
			म_लिखो("vmx[%d][1]: %lx load[%d] %lx\n",
					i, vmx[i][1], 65 + 2 * i,
					load[65 + 2 * i]);
			वापस TEST_FAIL;
		पूर्ण
		#अन्यथा  /*
			* In LE each value pair is stored in an
			* alternate manner.
			*/
		अगर ((vmx[i][0] != load[65 + 2 * i]) ||
				(vmx[i][1] != load[64 + 2 * i])) अणु
			म_लिखो("vmx[%d][0]: %lx load[%d] %lx\n",
					i, vmx[i][0], 65 + 2 * i,
					load[65 + 2 * i]);
			म_लिखो("vmx[%d][1]: %lx load[%d] %lx\n",
					i, vmx[i][1], 64 + 2 * i,
					load[64 + 2 * i]);
			वापस TEST_FAIL;
		पूर्ण
		#पूर्ण_अगर
	पूर्ण
	वापस TEST_PASS;
पूर्ण

/*
 * अचिन्हित दीर्घ store[128]
 * अचिन्हित दीर्घ load[128]
 */
पूर्णांक compare_vsx_vmx(अचिन्हित दीर्घ *store, अचिन्हित दीर्घ *load)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VSX_MAX; i++) अणु
		अगर (store[1 + 2 * i] != load[1 + 2 * i]) अणु
			म_लिखो("store[%d]: %lx load[%d] %lx\n",
					1 + 2 * i, store[i],
					1 + 2 * i, load[i]);
			वापस TEST_FAIL;
		पूर्ण
	पूर्ण

	#अगर __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	क्रम (i = 64; i < VEC_MAX; i++) अणु
		अगर (store[i] != load[i]) अणु
			म_लिखो("store[%d]: %lx load[%d] %lx\n",
					i, store[i], i, load[i]);
			वापस TEST_FAIL;
		पूर्ण
	पूर्ण
	#अन्यथा	/* In LE each value pair is stored in an alternate manner */
	क्रम (i = 64; i < VEC_MAX; i++) अणु
		अगर (!(i % 2) && (store[i] != load[i+1])) अणु
			म_लिखो("store[%d]: %lx load[%d] %lx\n",
					i, store[i], i+1, load[i+1]);
			वापस TEST_FAIL;
		पूर्ण
		अगर ((i % 2) && (store[i] != load[i-1])) अणु
			म_लिखो("here store[%d]: %lx load[%d] %lx\n",
					i, store[i], i-1, load[i-1]);
			वापस TEST_FAIL;
		पूर्ण
	पूर्ण
	#पूर्ण_अगर
	वापस TEST_PASS;
पूर्ण

व्योम load_vsx_vmx(अचिन्हित दीर्घ *load, अचिन्हित दीर्घ *vsx,
		अचिन्हित दीर्घ vmx[][2])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VSX_MAX; i++)
		vsx[i] = load[1 + 2 * i];

	क्रम (i = 0; i < VMX_MAX; i++) अणु
		vmx[i][0] = load[64 + 2 * i];
		vmx[i][1] = load[65 + 2 * i];
	पूर्ण
पूर्ण

व्योम loadvsx(व्योम *p, पूर्णांक पंचांगp);
व्योम storevsx(व्योम *p, पूर्णांक पंचांगp);
