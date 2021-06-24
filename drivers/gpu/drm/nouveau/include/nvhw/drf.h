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
#अगर_अघोषित __NVHW_DRF_H__
#घोषणा __NVHW_DRF_H__

/* Helpers common to all DRF accessors. */
#घोषणा DRF_LO(drf)    (0 ? drf)
#घोषणा DRF_HI(drf)    (1 ? drf)
#घोषणा DRF_BITS(drf)  (DRF_HI(drf) - DRF_LO(drf) + 1)
#घोषणा DRF_MASK(drf)  (~0ULL >> (64 - DRF_BITS(drf)))
#घोषणा DRF_SMASK(drf) (DRF_MASK(drf) << DRF_LO(drf))

/* Helpers क्रम DRF-MW accessors. */
#घोषणा DRF_MX_MW(drf)      drf
#घोषणा DRF_MX(drf)         DRF_MX_##drf
#घोषणा DRF_MW(drf)         DRF_MX(drf)
#घोषणा DRF_MW_SPANS(o,drf) (DRF_LW_IDX((o),drf) != DRF_HW_IDX((o),drf))
#घोषणा DRF_MW_SIZE(o)      (माप((o)[0]) * 8)

#घोषणा DRF_LW_IDX(o,drf)   (DRF_LO(DRF_MW(drf)) / DRF_MW_SIZE(o))
#घोषणा DRF_LW_LO(o,drf)    (DRF_LO(DRF_MW(drf)) % DRF_MW_SIZE(o))
#घोषणा DRF_LW_HI(o,drf)    (DRF_MW_SPANS((o),drf) ? (DRF_MW_SIZE(o) - 1) : DRF_HW_HI((o),drf))
#घोषणा DRF_LW_BITS(o,drf)  (DRF_LW_HI((o),drf) - DRF_LW_LO((o),drf) + 1)
#घोषणा DRF_LW_MASK(o,drf)  (~0ULL >> (64 - DRF_LW_BITS((o),drf)))
#घोषणा DRF_LW_SMASK(o,drf) (DRF_LW_MASK((o),drf) << DRF_LW_LO((o),drf))
#घोषणा DRF_LW_GET(o,drf)   (((o)[DRF_LW_IDX((o),drf)] >> DRF_LW_LO((o),drf)) & DRF_LW_MASK((o),drf))
#घोषणा DRF_LW_VAL(o,drf,v) (((v) & DRF_LW_MASK((o),drf)) << DRF_LW_LO((o),drf))
#घोषणा DRF_LW_CLR(o,drf)   ((o)[DRF_LW_IDX((o),drf)] & ~DRF_LW_SMASK((o),drf))
#घोषणा DRF_LW_SET(o,drf,v) (DRF_LW_CLR((o),drf) | DRF_LW_VAL((o),drf,(v)))

#घोषणा DRF_HW_IDX(o,drf)   (DRF_HI(DRF_MW(drf)) / DRF_MW_SIZE(o))
#घोषणा DRF_HW_LO(o,drf)    0
#घोषणा DRF_HW_HI(o,drf)    (DRF_HI(DRF_MW(drf)) % DRF_MW_SIZE(o))
#घोषणा DRF_HW_BITS(o,drf)  (DRF_HW_HI((o),drf) - DRF_HW_LO((o),drf) + 1)
#घोषणा DRF_HW_MASK(o,drf)  (~0ULL >> (64 - DRF_HW_BITS((o),drf)))
#घोषणा DRF_HW_SMASK(o,drf) (DRF_HW_MASK((o),drf) << DRF_HW_LO((o),drf))
#घोषणा DRF_HW_GET(o,drf)   ((o)[DRF_HW_IDX(o,drf)] & DRF_HW_SMASK((o),drf))
#घोषणा DRF_HW_VAL(o,drf,v) (((दीर्घ दीर्घ)(v) >> DRF_LW_BITS((o),drf)) & DRF_HW_SMASK((o),drf))
#घोषणा DRF_HW_CLR(o,drf)   ((o)[DRF_HW_IDX((o),drf)] & ~DRF_HW_SMASK((o),drf))
#घोषणा DRF_HW_SET(o,drf,v) (DRF_HW_CLR((o),drf) | DRF_HW_VAL((o),drf,(v)))

/* DRF accessors. */
#घोषणा NVVAL_X(drf,v) (((v) & DRF_MASK(drf)) << DRF_LO(drf))
#घोषणा NVVAL_N(X,d,r,f,  v) NVVAL_X(d##_##r##_##f, (v))
#घोषणा NVVAL_I(X,d,r,f,i,v) NVVAL_X(d##_##r##_##f(i), (v))
#घोषणा NVVAL_(X,_1,_2,_3,_4,_5,IMPL,...) IMPL
#घोषणा NVVAL(A...) NVVAL_(X, ##A, NVVAL_I, NVVAL_N)(X, ##A)

#घोषणा NVDEF_N(X,d,r,f,  v) NVVAL_X(d##_##r##_##f, d##_##r##_##f##_##v)
#घोषणा NVDEF_I(X,d,r,f,i,v) NVVAL_X(d##_##r##_##f(i), d##_##r##_##f##_##v)
#घोषणा NVDEF_(X,_1,_2,_3,_4,_5,IMPL,...) IMPL
#घोषणा NVDEF(A...) NVDEF_(X, ##A, NVDEF_I, NVDEF_N)(X, ##A)

#घोषणा NVVAL_GET_X(o,drf) (((o) >> DRF_LO(drf)) & DRF_MASK(drf))
#घोषणा NVVAL_GET_N(X,o,d,r,f  ) NVVAL_GET_X(o, d##_##r##_##f)
#घोषणा NVVAL_GET_I(X,o,d,r,f,i) NVVAL_GET_X(o, d##_##r##_##f(i))
#घोषणा NVVAL_GET_(X,_1,_2,_3,_4,_5,IMPL,...) IMPL
#घोषणा NVVAL_GET(A...) NVVAL_GET_(X, ##A, NVVAL_GET_I, NVVAL_GET_N)(X, ##A)

#घोषणा NVVAL_TEST_X(o,drf,cmp,drfv) (NVVAL_GET_X((o), drf) cmp drfv)
#घोषणा NVVAL_TEST_N(X,o,d,r,f,  cmp,v) NVVAL_TEST_X(o, d##_##r##_##f   , cmp, (v))
#घोषणा NVVAL_TEST_I(X,o,d,r,f,i,cmp,v) NVVAL_TEST_X(o, d##_##r##_##f(i), cmp, (v))
#घोषणा NVVAL_TEST_(X,_1,_2,_3,_4,_5,_6,_7,IMPL,...) IMPL
#घोषणा NVVAL_TEST(A...) NVVAL_TEST_(X, ##A, NVVAL_TEST_I, NVVAL_TEST_N)(X, ##A)

#घोषणा NVDEF_TEST_N(X,o,d,r,f,  cmp,v) NVVAL_TEST_X(o, d##_##r##_##f   , cmp, d##_##r##_##f##_##v)
#घोषणा NVDEF_TEST_I(X,o,d,r,f,i,cmp,v) NVVAL_TEST_X(o, d##_##r##_##f(i), cmp, d##_##r##_##f##_##v)
#घोषणा NVDEF_TEST_(X,_1,_2,_3,_4,_5,_6,_7,IMPL,...) IMPL
#घोषणा NVDEF_TEST(A...) NVDEF_TEST_(X, ##A, NVDEF_TEST_I, NVDEF_TEST_N)(X, ##A)

#घोषणा NVVAL_SET_X(o,drf,v) (((o) & ~DRF_SMASK(drf)) | NVVAL_X(drf, (v)))
#घोषणा NVVAL_SET_N(X,o,d,r,f,  v) NVVAL_SET_X(o, d##_##r##_##f, (v))
#घोषणा NVVAL_SET_I(X,o,d,r,f,i,v) NVVAL_SET_X(o, d##_##r##_##f(i), (v))
#घोषणा NVVAL_SET_(X,_1,_2,_3,_4,_5,_6,IMPL,...) IMPL
#घोषणा NVVAL_SET(A...) NVVAL_SET_(X, ##A, NVVAL_SET_I, NVVAL_SET_N)(X, ##A)

#घोषणा NVDEF_SET_N(X,o,d,r,f,  v) NVVAL_SET_X(o, d##_##r##_##f,    d##_##r##_##f##_##v)
#घोषणा NVDEF_SET_I(X,o,d,r,f,i,v) NVVAL_SET_X(o, d##_##r##_##f(i), d##_##r##_##f##_##v)
#घोषणा NVDEF_SET_(X,_1,_2,_3,_4,_5,_6,IMPL,...) IMPL
#घोषणा NVDEF_SET(A...) NVDEF_SET_(X, ##A, NVDEF_SET_I, NVDEF_SET_N)(X, ##A)

/* DRF-MW accessors. */
#घोषणा NVVAL_MW_GET_X(o,drf)                                                       \
	((DRF_MW_SPANS((o),drf) ?                                                   \
	  (DRF_HW_GET((o),drf) << DRF_LW_BITS((o),drf)) : 0) | DRF_LW_GET((o),drf))
#घोषणा NVVAL_MW_GET_N(X,o,d,r,f  ) NVVAL_MW_GET_X((o), d##_##r##_##f)
#घोषणा NVVAL_MW_GET_I(X,o,d,r,f,i) NVVAL_MW_GET_X((o), d##_##r##_##f(i))
#घोषणा NVVAL_MW_GET_(X,_1,_2,_3,_4,_5,IMPL,...) IMPL
#घोषणा NVVAL_MW_GET(A...) NVVAL_MW_GET_(X, ##A, NVVAL_MW_GET_I, NVVAL_MW_GET_N)(X, ##A)

#घोषणा NVVAL_MW_SET_X(o,drf,v) करो अणु                                           \
	(o)[DRF_LW_IDX((o),drf)] = DRF_LW_SET((o),drf,(v));                    \
	अगर (DRF_MW_SPANS((o),drf))                                             \
		(o)[DRF_HW_IDX((o),drf)] = DRF_HW_SET((o),drf,(v));            \
पूर्ण जबतक(0)
#घोषणा NVVAL_MW_SET_N(X,o,d,r,f,  v) NVVAL_MW_SET_X((o), d##_##r##_##f, (v))
#घोषणा NVVAL_MW_SET_I(X,o,d,r,f,i,v) NVVAL_MW_SET_X((o), d##_##r##_##f(i), (v))
#घोषणा NVVAL_MW_SET_(X,_1,_2,_3,_4,_5,_6,IMPL,...) IMPL
#घोषणा NVVAL_MW_SET(A...) NVVAL_MW_SET_(X, ##A, NVVAL_MW_SET_I, NVVAL_MW_SET_N)(X, ##A)

#घोषणा NVDEF_MW_SET_N(X,o,d,r,f,  v) NVVAL_MW_SET_X(o, d##_##r##_##f,    d##_##r##_##f##_##v)
#घोषणा NVDEF_MW_SET_I(X,o,d,r,f,i,v) NVVAL_MW_SET_X(o, d##_##r##_##f(i), d##_##r##_##f##_##v)
#घोषणा NVDEF_MW_SET_(X,_1,_2,_3,_4,_5,_6,IMPL,...) IMPL
#घोषणा NVDEF_MW_SET(A...) NVDEF_MW_SET_(X, ##A, NVDEF_MW_SET_I, NVDEF_MW_SET_N)(X, ##A)

/* Helper क्रम पढ़ोing an arbitrary object. */
#घोषणा DRF_RD_X(e,p,o,dr) e((p), (o), dr)
#घोषणा DRF_RD_N(X,e,p,o,d,r  ) DRF_RD_X(e, (p), (o), d##_##r)
#घोषणा DRF_RD_I(X,e,p,o,d,r,i) DRF_RD_X(e, (p), (o), d##_##r(i))
#घोषणा DRF_RD_(X,_1,_2,_3,_4,_5,_6,IMPL,...) IMPL
#घोषणा DRF_RD(A...) DRF_RD_(X, ##A, DRF_RD_I, DRF_RD_N)(X, ##A)

/* Helper क्रम writing an arbitrary object. */
#घोषणा DRF_WR_X(e,p,o,dr,v) e((p), (o), dr, (v))
#घोषणा DRF_WR_N(X,e,p,o,d,r,  v) DRF_WR_X(e, (p), (o), d##_##r   , (v))
#घोषणा DRF_WR_I(X,e,p,o,d,r,i,v) DRF_WR_X(e, (p), (o), d##_##r(i), (v))
#घोषणा DRF_WR_(X,_1,_2,_3,_4,_5,_6,_7,IMPL,...) IMPL
#घोषणा DRF_WR(A...) DRF_WR_(X, ##A, DRF_WR_I, DRF_WR_N)(X, ##A)

/* Helper क्रम modअगरying an arbitrary object. */
#घोषणा DRF_MR_X(er,ew,ty,p,o,dr,m,v) (अणु               \
	ty _t = DRF_RD_X(er, (p), (o), dr);            \
	DRF_WR_X(ew, (p), (o), dr, (_t & ~(m)) | (v)); \
	_t;                                            \
पूर्ण)
#घोषणा DRF_MR_N(X,er,ew,ty,p,o,d,r  ,m,v) DRF_MR_X(er, ew, ty, (p), (o), d##_##r   , (m), (v))
#घोषणा DRF_MR_I(X,er,ew,ty,p,o,d,r,i,m,v) DRF_MR_X(er, ew, ty, (p), (o), d##_##r(i), (m), (v))
#घोषणा DRF_MR_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,IMPL,...) IMPL
#घोषणा DRF_MR(A...) DRF_MR_(X, ##A, DRF_MR_I, DRF_MR_N)(X, ##A)

/* Helper क्रम extracting a field value from arbitrary object. */
#घोषणा DRF_RV_X(e,p,o,dr,drf) NVVAL_GET_X(DRF_RD_X(e, (p), (o), dr), drf)
#घोषणा DRF_RV_N(X,e,p,o,d,r,  f) DRF_RV_X(e, (p), (o), d##_##r   , d##_##r##_##f)
#घोषणा DRF_RV_I(X,e,p,o,d,r,i,f) DRF_RV_X(e, (p), (o), d##_##r(i), d##_##r##_##f)
#घोषणा DRF_RV_(X,_1,_2,_3,_4,_5,_6,_7,IMPL,...) IMPL
#घोषणा DRF_RV(A...) DRF_RV_(X, ##A, DRF_RV_I, DRF_RV_N)(X, ##A)

/* Helper क्रम writing field value to arbitrary object (all other bits cleared). */
#घोषणा DRF_WV_N(X,e,p,o,d,r,  f,v)                                    \
	DRF_WR_X(e, (p), (o), d##_##r   , NVVAL_X(d##_##r##_##f, (v)))
#घोषणा DRF_WV_I(X,e,p,o,d,r,i,f,v)                                    \
	DRF_WR_X(e, (p), (o), d##_##r(i), NVVAL_X(d##_##r##_##f, (v)))
#घोषणा DRF_WV_(X,_1,_2,_3,_4,_5,_6,_7,_8,IMPL,...) IMPL
#घोषणा DRF_WV(A...) DRF_WV_(X, ##A, DRF_WV_I, DRF_WV_N)(X, ##A)

/* Helper क्रम writing field definition to arbitrary object (all other bits cleared). */
#घोषणा DRF_WD_N(X,e,p,o,d,r,  f,v)                                                    \
	DRF_WR_X(e, (p), (o), d##_##r   , NVVAL_X(d##_##r##_##f, d##_##r##_##f##_##v))
#घोषणा DRF_WD_I(X,e,p,o,d,r,i,f,v)                                                    \
	DRF_WR_X(e, (p), (o), d##_##r(i), NVVAL_X(d##_##r##_##f, d##_##r##_##f##_##v))
#घोषणा DRF_WD_(X,_1,_2,_3,_4,_5,_6,_7,_8,IMPL,...) IMPL
#घोषणा DRF_WD(A...) DRF_WD_(X, ##A, DRF_WD_I, DRF_WD_N)(X, ##A)

/* Helper क्रम modअगरying field value in arbitrary object. */
#घोषणा DRF_MV_N(X,er,ew,ty,p,o,d,r,  f,v)                                               \
	NVVAL_GET_X(DRF_MR_X(er, ew, ty, (p), (o), d##_##r   , DRF_SMASK(d##_##r##_##f), \
		    NVVAL_X(d##_##r##_##f, (v))), d##_##r##_##f)
#घोषणा DRF_MV_I(X,er,ew,ty,p,o,d,r,i,f,v)                                               \
	NVVAL_GET_X(DRF_MR_X(er, ew, ty, (p), (o), d##_##r(i), DRF_SMASK(d##_##r##_##f), \
		    NVVAL_X(d##_##r##_##f, (v))), d##_##r##_##f)
#घोषणा DRF_MV_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,IMPL,...) IMPL
#घोषणा DRF_MV(A...) DRF_MV_(X, ##A, DRF_MV_I, DRF_MV_N)(X, ##A)

/* Helper क्रम modअगरying field definition in arbitrary object. */
#घोषणा DRF_MD_N(X,er,ew,ty,p,o,d,r,  f,v)                                               \
	NVVAL_GET_X(DRF_MR_X(er, ew, ty, (p), (o), d##_##r   , DRF_SMASK(d##_##r##_##f), \
		    NVVAL_X(d##_##r##_##f, d##_##r##_##f##_##v)), d##_##r##_##f)
#घोषणा DRF_MD_I(X,er,ew,ty,p,o,d,r,i,f,v)                                               \
	NVVAL_GET_X(DRF_MR_X(er, ew, ty, (p), (o), d##_##r(i), DRF_SMASK(d##_##r##_##f), \
		    NVVAL_X(d##_##r##_##f, d##_##r##_##f##_##v)), d##_##r##_##f)
#घोषणा DRF_MD_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,IMPL,...) IMPL
#घोषणा DRF_MD(A...) DRF_MD_(X, ##A, DRF_MD_I, DRF_MD_N)(X, ##A)

/* Helper क्रम testing against field value in aribtrary object */
#घोषणा DRF_TV_N(X,e,p,o,d,r,  f,cmp,v)                                          \
	NVVAL_TEST_X(DRF_RD_X(e, (p), (o), d##_##r   ), d##_##r##_##f, cmp, (v))
#घोषणा DRF_TV_I(X,e,p,o,d,r,i,f,cmp,v)                                          \
	NVVAL_TEST_X(DRF_RD_X(e, (p), (o), d##_##r(i)), d##_##r##_##f, cmp, (v))
#घोषणा DRF_TV_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,IMPL,...) IMPL
#घोषणा DRF_TV(A...) DRF_TV_(X, ##A, DRF_TV_I, DRF_TV_N)(X, ##A)

/* Helper क्रम testing against field definition in aribtrary object */
#घोषणा DRF_TD_N(X,e,p,o,d,r,  f,cmp,v)                                                          \
	NVVAL_TEST_X(DRF_RD_X(e, (p), (o), d##_##r   ), d##_##r##_##f, cmp, d##_##r##_##f##_##v)
#घोषणा DRF_TD_I(X,e,p,o,d,r,i,f,cmp,v)                                                          \
	NVVAL_TEST_X(DRF_RD_X(e, (p), (o), d##_##r(i)), d##_##r##_##f, cmp, d##_##r##_##f##_##v)
#घोषणा DRF_TD_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,IMPL,...) IMPL
#घोषणा DRF_TD(A...) DRF_TD_(X, ##A, DRF_TD_I, DRF_TD_N)(X, ##A)
#पूर्ण_अगर
