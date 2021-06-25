<शैली गुरु>
/*
 * Copyright 2019 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित __NVIF_PUSH_H__
#घोषणा __NVIF_PUSH_H__
#समावेश <nvअगर/स्मृति.स>
#समावेश <nvअगर/म_लिखो.h>

#समावेश <nvhw/drf.h>

काष्ठा nvअगर_push अणु
	पूर्णांक (*रुको)(काष्ठा nvअगर_push *push, u32 size);
	व्योम (*kick)(काष्ठा nvअगर_push *push);

	काष्ठा nvअगर_mem mem;

	u32 *bgn;
	u32 *cur;
	u32 *seg;
	u32 *end;
पूर्ण;

अटल अंतरभूत __must_check पूर्णांक
PUSH_WAIT(काष्ठा nvअगर_push *push, u32 size)
अणु
	अगर (push->cur + size >= push->end) अणु
		पूर्णांक ret = push->रुको(push, size);
		अगर (ret)
			वापस ret;
	पूर्ण
#अगर_घोषित CONFIG_NOUVEAU_DEBUG_PUSH
	push->seg = push->cur + size;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
PUSH_KICK(काष्ठा nvअगर_push *push)
अणु
	push->kick(push);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NOUVEAU_DEBUG_PUSH
#घोषणा PUSH_PRINTF(p,f,a...) करो अणु                              \
	काष्ठा nvअगर_push *_ppp = (p);                           \
	u32 __o = _ppp->cur - (u32 *)_ppp->mem.object.map.ptr;  \
	NVIF_DEBUG(&_ppp->mem.object, "%08x: "f, __o * 4, ##a); \
	(व्योम)__o;                                              \
पूर्ण जबतक(0)
#घोषणा PUSH_ASSERT_ON(a,b) WARN((a), b)
#अन्यथा
#घोषणा PUSH_PRINTF(p,f,a...)
#घोषणा PUSH_ASSERT_ON(a, b)
#पूर्ण_अगर

#घोषणा PUSH_ASSERT(a,b) करो अणु                                             \
	अटल_निश्चित(                                                    \
		__builtin_choose_expr(__builtin_स्थिरant_p(a), (a), 1), b \
	);                                                                \
	PUSH_ASSERT_ON(!(a), b);                                          \
पूर्ण जबतक(0)

#घोषणा PUSH_DATA__(p,d,f,a...) करो अणु                       \
	काष्ठा nvअगर_push *_p = (p);                        \
	u32 _d = (d);                                      \
	PUSH_ASSERT(_p->cur < _p->seg, "segment overrun"); \
	PUSH_ASSERT(_p->cur < _p->end, "pushbuf overrun"); \
	PUSH_PRINTF(_p, "%08x"f, _d, ##a);                 \
	*_p->cur++ = _d;                                   \
पूर्ण जबतक(0)

#घोषणा PUSH_DATA_(X,p,m,i0,i1,d,s,f,a...) PUSH_DATA__((p), (d), "-> "#m f, ##a)
#घोषणा PUSH_DATA(p,d) PUSH_DATA__((p), (d), " data - %s", __func__)

//XXX: error-check this against *real* pushbuffer end?
#घोषणा PUSH_RSVD(p,d) करो अणु          \
	काष्ठा nvअगर_push *__p = (p); \
	__p->seg++;                  \
	__p->end++;                  \
	d;                           \
पूर्ण जबतक(0)

#अगर_घोषित CONFIG_NOUVEAU_DEBUG_PUSH
#घोषणा PUSH_DATAp(X,p,m,i,o,d,s,f,a...) करो अणु                                     \
	काष्ठा nvअगर_push *_pp = (p);                                              \
	स्थिर u32 *_dd = (d);                                                     \
	u32 _s = (s), _i = (i?PUSH_##o##_INC);                                    \
	अगर (_s--) अणु                                                               \
		PUSH_DATA_(X, _pp, X##m, i0, i1, *_dd++, 1, "+0x%x", 0);          \
		जबतक (_s--) अणु                                                    \
			PUSH_DATA_(X, _pp, X##m, i0, i1, *_dd++, 1, "+0x%x", _i); \
			_i += (0?PUSH_##o##_INC);                                 \
		पूर्ण                                                                 \
	पूर्ण                                                                         \
पूर्ण जबतक(0)
#अन्यथा
#घोषणा PUSH_DATAp(X,p,m,i,o,d,s,f,a...) करो अणु                    \
	काष्ठा nvअगर_push *_p = (p);                              \
	u32 _s = (s);                                            \
	PUSH_ASSERT(_p->cur + _s <= _p->seg, "segment overrun"); \
	PUSH_ASSERT(_p->cur + _s <= _p->end, "pushbuf overrun"); \
	स_नकल(_p->cur, (d), _s << 2);                           \
	_p->cur += _s;                                           \
पूर्ण जबतक(0)
#पूर्ण_अगर

#घोषणा PUSH_1(X,f,ds,n,o,p,s,mA,dA) करो अणु                             \
	PUSH_##o##_HDR((p), s, mA, (ds)+(n));                         \
	PUSH_##f(X, (p), X##mA, 1, o, (dA), ds, "");                  \
पूर्ण जबतक(0)
#घोषणा PUSH_2(X,f,ds,n,o,p,s,mB,dB,mA,dA,a...) करो अणु                  \
	PUSH_ASSERT((mB) - (mA) == (1?PUSH_##o##_INC), "mthd1");      \
	PUSH_1(X, DATA_, 1, (ds) + (n), o, (p), s, X##mA, (dA), ##a); \
	PUSH_##f(X, (p), X##mB, 0, o, (dB), ds, "");                  \
पूर्ण जबतक(0)
#घोषणा PUSH_3(X,f,ds,n,o,p,s,mB,dB,mA,dA,a...) करो अणु                  \
	PUSH_ASSERT((mB) - (mA) == (0?PUSH_##o##_INC), "mthd2");      \
	PUSH_2(X, DATA_, 1, (ds) + (n), o, (p), s, X##mA, (dA), ##a); \
	PUSH_##f(X, (p), X##mB, 0, o, (dB), ds, "");                  \
पूर्ण जबतक(0)
#घोषणा PUSH_4(X,f,ds,n,o,p,s,mB,dB,mA,dA,a...) करो अणु                  \
	PUSH_ASSERT((mB) - (mA) == (0?PUSH_##o##_INC), "mthd3");      \
	PUSH_3(X, DATA_, 1, (ds) + (n), o, (p), s, X##mA, (dA), ##a); \
	PUSH_##f(X, (p), X##mB, 0, o, (dB), ds, "");                  \
पूर्ण जबतक(0)
#घोषणा PUSH_5(X,f,ds,n,o,p,s,mB,dB,mA,dA,a...) करो अणु                  \
	PUSH_ASSERT((mB) - (mA) == (0?PUSH_##o##_INC), "mthd4");      \
	PUSH_4(X, DATA_, 1, (ds) + (n), o, (p), s, X##mA, (dA), ##a); \
	PUSH_##f(X, (p), X##mB, 0, o, (dB), ds, "");                  \
पूर्ण जबतक(0)
#घोषणा PUSH_6(X,f,ds,n,o,p,s,mB,dB,mA,dA,a...) करो अणु                  \
	PUSH_ASSERT((mB) - (mA) == (0?PUSH_##o##_INC), "mthd5");      \
	PUSH_5(X, DATA_, 1, (ds) + (n), o, (p), s, X##mA, (dA), ##a); \
	PUSH_##f(X, (p), X##mB, 0, o, (dB), ds, "");                  \
पूर्ण जबतक(0)
#घोषणा PUSH_7(X,f,ds,n,o,p,s,mB,dB,mA,dA,a...) करो अणु                  \
	PUSH_ASSERT((mB) - (mA) == (0?PUSH_##o##_INC), "mthd6");      \
	PUSH_6(X, DATA_, 1, (ds) + (n), o, (p), s, X##mA, (dA), ##a); \
	PUSH_##f(X, (p), X##mB, 0, o, (dB), ds, "");                  \
पूर्ण जबतक(0)
#घोषणा PUSH_8(X,f,ds,n,o,p,s,mB,dB,mA,dA,a...) करो अणु                  \
	PUSH_ASSERT((mB) - (mA) == (0?PUSH_##o##_INC), "mthd7");      \
	PUSH_7(X, DATA_, 1, (ds) + (n), o, (p), s, X##mA, (dA), ##a); \
	PUSH_##f(X, (p), X##mB, 0, o, (dB), ds, "");                  \
पूर्ण जबतक(0)
#घोषणा PUSH_9(X,f,ds,n,o,p,s,mB,dB,mA,dA,a...) करो अणु                  \
	PUSH_ASSERT((mB) - (mA) == (0?PUSH_##o##_INC), "mthd8");      \
	PUSH_8(X, DATA_, 1, (ds) + (n), o, (p), s, X##mA, (dA), ##a); \
	PUSH_##f(X, (p), X##mB, 0, o, (dB), ds, "");                  \
पूर्ण जबतक(0)
#घोषणा PUSH_10(X,f,ds,n,o,p,s,mB,dB,mA,dA,a...) करो अणु                 \
	PUSH_ASSERT((mB) - (mA) == (0?PUSH_##o##_INC), "mthd9");      \
	PUSH_9(X, DATA_, 1, (ds) + (n), o, (p), s, X##mA, (dA), ##a); \
	PUSH_##f(X, (p), X##mB, 0, o, (dB), ds, "");                  \
पूर्ण जबतक(0)

#घोषणा PUSH_1D(X,o,p,s,mA,dA)                         \
	PUSH_1(X, DATA_, 1, 0, o, (p), s, X##mA, (dA))
#घोषणा PUSH_2D(X,o,p,s,mA,dA,mB,dB)                   \
	PUSH_2(X, DATA_, 1, 0, o, (p), s, X##mB, (dB), \
					  X##mA, (dA))
#घोषणा PUSH_3D(X,o,p,s,mA,dA,mB,dB,mC,dC)             \
	PUSH_3(X, DATA_, 1, 0, o, (p), s, X##mC, (dC), \
					  X##mB, (dB), \
					  X##mA, (dA))
#घोषणा PUSH_4D(X,o,p,s,mA,dA,mB,dB,mC,dC,mD,dD)       \
	PUSH_4(X, DATA_, 1, 0, o, (p), s, X##mD, (dD), \
					  X##mC, (dC), \
					  X##mB, (dB), \
					  X##mA, (dA))
#घोषणा PUSH_5D(X,o,p,s,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE) \
	PUSH_5(X, DATA_, 1, 0, o, (p), s, X##mE, (dE), \
					  X##mD, (dD), \
					  X##mC, (dC), \
					  X##mB, (dB), \
					  X##mA, (dA))
#घोषणा PUSH_6D(X,o,p,s,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,dF) \
	PUSH_6(X, DATA_, 1, 0, o, (p), s, X##mF, (dF),       \
					  X##mE, (dE),       \
					  X##mD, (dD),       \
					  X##mC, (dC),       \
					  X##mB, (dB),       \
					  X##mA, (dA))
#घोषणा PUSH_7D(X,o,p,s,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,dF,mG,dG) \
	PUSH_7(X, DATA_, 1, 0, o, (p), s, X##mG, (dG),             \
					  X##mF, (dF),             \
					  X##mE, (dE),             \
					  X##mD, (dD),             \
					  X##mC, (dC),             \
					  X##mB, (dB),             \
					  X##mA, (dA))
#घोषणा PUSH_8D(X,o,p,s,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,dF,mG,dG,mH,dH) \
	PUSH_8(X, DATA_, 1, 0, o, (p), s, X##mH, (dH),                   \
					  X##mG, (dG),                   \
					  X##mF, (dF),                   \
					  X##mE, (dE),                   \
					  X##mD, (dD),                   \
					  X##mC, (dC),                   \
					  X##mB, (dB),                   \
					  X##mA, (dA))
#घोषणा PUSH_9D(X,o,p,s,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,dF,mG,dG,mH,dH,mI,dI) \
	PUSH_9(X, DATA_, 1, 0, o, (p), s, X##mI, (dI),                         \
					  X##mH, (dH),                         \
					  X##mG, (dG),                         \
					  X##mF, (dF),                         \
					  X##mE, (dE),                         \
					  X##mD, (dD),                         \
					  X##mC, (dC),                         \
					  X##mB, (dB),                         \
					  X##mA, (dA))
#घोषणा PUSH_10D(X,o,p,s,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,dF,mG,dG,mH,dH,mI,dI,mJ,dJ) \
	PUSH_10(X, DATA_, 1, 0, o, (p), s, X##mJ, (dJ),                               \
					   X##mI, (dI),                               \
					   X##mH, (dH),                               \
					   X##mG, (dG),                               \
					   X##mF, (dF),                               \
					   X##mE, (dE),                               \
					   X##mD, (dD),                               \
					   X##mC, (dC),                               \
					   X##mB, (dB),                               \
					   X##mA, (dA))

#घोषणा PUSH_1P(X,o,p,s,mA,dp,ds)                       \
	PUSH_1(X, DATAp, ds, 0, o, (p), s, X##mA, (dp))
#घोषणा PUSH_2P(X,o,p,s,mA,dA,mB,dp,ds)                 \
	PUSH_2(X, DATAp, ds, 0, o, (p), s, X##mB, (dp), \
					   X##mA, (dA))
#घोषणा PUSH_3P(X,o,p,s,mA,dA,mB,dB,mC,dp,ds)           \
	PUSH_3(X, DATAp, ds, 0, o, (p), s, X##mC, (dp), \
					   X##mB, (dB), \
					   X##mA, (dA))

#घोषणा PUSH_(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,IMPL,...) IMPL
#घोषणा PUSH(A...) PUSH_(A, PUSH_10P, PUSH_10D,          \
			    PUSH_9P , PUSH_9D,           \
			    PUSH_8P , PUSH_8D,           \
			    PUSH_7P , PUSH_7D,           \
			    PUSH_6P , PUSH_6D,           \
			    PUSH_5P , PUSH_5D,           \
			    PUSH_4P , PUSH_4D,           \
			    PUSH_3P , PUSH_3D,           \
			    PUSH_2P , PUSH_2D,           \
			    PUSH_1P , PUSH_1D)(, ##A)

#घोषणा PUSH_NVIM(p,c,m,d) करो अणु             \
	काष्ठा nvअगर_push *__p = (p);        \
	u32 __d = (d);                      \
	PUSH_IMMD_HDR(__p, c, m, __d);      \
	__p->cur--;                         \
	PUSH_PRINTF(__p, "%08x-> "#m, __d); \
	__p->cur++;                         \
पूर्ण जबतक(0)
#घोषणा PUSH_NVSQ(A...) PUSH(MTHD, ##A)
#घोषणा PUSH_NV1I(A...) PUSH(1INC, ##A)
#घोषणा PUSH_NVNI(A...) PUSH(NINC, ##A)


#घोषणा PUSH_NV_1(X,o,p,c,mA,d...) \
       PUSH_##o(p,c,c##_##mA,d)
#घोषणा PUSH_NV_2(X,o,p,c,mA,dA,mB,d...) \
       PUSH_##o(p,c,c##_##mA,dA,         \
		    c##_##mB,d)
#घोषणा PUSH_NV_3(X,o,p,c,mA,dA,mB,dB,mC,d...) \
       PUSH_##o(p,c,c##_##mA,dA,               \
		    c##_##mB,dB,               \
		    c##_##mC,d)
#घोषणा PUSH_NV_4(X,o,p,c,mA,dA,mB,dB,mC,dC,mD,d...) \
       PUSH_##o(p,c,c##_##mA,dA,                     \
		    c##_##mB,dB,                     \
		    c##_##mC,dC,                     \
		    c##_##mD,d)
#घोषणा PUSH_NV_5(X,o,p,c,mA,dA,mB,dB,mC,dC,mD,dD,mE,d...) \
       PUSH_##o(p,c,c##_##mA,dA,                           \
		    c##_##mB,dB,                           \
		    c##_##mC,dC,                           \
		    c##_##mD,dD,                           \
		    c##_##mE,d)
#घोषणा PUSH_NV_6(X,o,p,c,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,d...) \
       PUSH_##o(p,c,c##_##mA,dA,                                 \
		    c##_##mB,dB,                                 \
		    c##_##mC,dC,                                 \
		    c##_##mD,dD,                                 \
		    c##_##mE,dE,                                 \
		    c##_##mF,d)
#घोषणा PUSH_NV_7(X,o,p,c,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,dF,mG,d...) \
       PUSH_##o(p,c,c##_##mA,dA,                                       \
		    c##_##mB,dB,                                       \
		    c##_##mC,dC,                                       \
		    c##_##mD,dD,                                       \
		    c##_##mE,dE,                                       \
		    c##_##mF,dF,                                       \
		    c##_##mG,d)
#घोषणा PUSH_NV_8(X,o,p,c,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,dF,mG,dG,mH,d...) \
       PUSH_##o(p,c,c##_##mA,dA,                                             \
		    c##_##mB,dB,                                             \
		    c##_##mC,dC,                                             \
		    c##_##mD,dD,                                             \
		    c##_##mE,dE,                                             \
		    c##_##mF,dF,                                             \
		    c##_##mG,dG,                                             \
		    c##_##mH,d)
#घोषणा PUSH_NV_9(X,o,p,c,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,dF,mG,dG,mH,dH,mI,d...) \
       PUSH_##o(p,c,c##_##mA,dA,                                                   \
		    c##_##mB,dB,                                                   \
		    c##_##mC,dC,                                                   \
		    c##_##mD,dD,                                                   \
		    c##_##mE,dE,                                                   \
		    c##_##mF,dF,                                                   \
		    c##_##mG,dG,                                                   \
		    c##_##mH,dH,                                                   \
		    c##_##mI,d)
#घोषणा PUSH_NV_10(X,o,p,c,mA,dA,mB,dB,mC,dC,mD,dD,mE,dE,mF,dF,mG,dG,mH,dH,mI,dI,mJ,d...) \
       PUSH_##o(p,c,c##_##mA,dA,                                                          \
		    c##_##mB,dB,                                                          \
		    c##_##mC,dC,                                                          \
		    c##_##mD,dD,                                                          \
		    c##_##mE,dE,                                                          \
		    c##_##mF,dF,                                                          \
		    c##_##mG,dG,                                                          \
		    c##_##mH,dH,                                                          \
		    c##_##mI,dI,                                                          \
		    c##_##mJ,d)

#घोषणा PUSH_NV_(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,IMPL,...) IMPL
#घोषणा PUSH_NV(A...) PUSH_NV_(A, PUSH_NV_10, PUSH_NV_10,       \
				  PUSH_NV_9 , PUSH_NV_9,        \
				  PUSH_NV_8 , PUSH_NV_8,        \
				  PUSH_NV_7 , PUSH_NV_7,        \
				  PUSH_NV_6 , PUSH_NV_6,        \
				  PUSH_NV_5 , PUSH_NV_5,        \
				  PUSH_NV_4 , PUSH_NV_4,        \
				  PUSH_NV_3 , PUSH_NV_3,        \
				  PUSH_NV_2 , PUSH_NV_2,        \
				  PUSH_NV_1 , PUSH_NV_1)(, ##A)

#घोषणा PUSH_IMMD(A...) PUSH_NV(NVIM, ##A)
#घोषणा PUSH_MTHD(A...) PUSH_NV(NVSQ, ##A)
#घोषणा PUSH_1INC(A...) PUSH_NV(NV1I, ##A)
#घोषणा PUSH_NINC(A...) PUSH_NV(NVNI, ##A)
#पूर्ण_अगर
