<शैली गुरु>
/*
 * Copyright (c) 2003 Patrick McHardy, <kaber@trash.net>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * 2003-10-17 - Ported from altq
 */
/*
 * Copyright (c) 1997-1999 Carnegie Mellon University. All Rights Reserved.
 *
 * Permission to use, copy, modअगरy, and distribute this software and
 * its करोcumentation is hereby granted (including क्रम commercial or
 * क्रम-profit use), provided that both the copyright notice and this
 * permission notice appear in all copies of the software, derivative
 * works, or modअगरied versions, and any portions thereof.
 *
 * THIS SOFTWARE IS EXPERIMENTAL AND IS KNOWN TO HAVE BUGS, SOME OF
 * WHICH MAY HAVE SERIOUS CONSEQUENCES.  CARNEGIE MELLON PROVIDES THIS
 * SOFTWARE IN ITS ``AS IS'' CONDITION, AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * Carnegie Mellon encourages (but करोes not require) users of this
 * software to वापस any improvements or extensions that they make,
 * and to grant Carnegie Mellon the rights to redistribute these
 * changes without encumbrance.
 */
/*
 * H-FSC is described in Proceedings of SIGCOMM'97,
 * "A Hierarchical Fair Service Curve Algorithm क्रम Link-Sharing,
 * Real-Time and Priority Service"
 * by Ion Stoica, Hui Zhang, and T. S. Eugene Ng.
 *
 * Oleg Cherevko <olwi@aq.ml.com.ua> added the upperlimit क्रम link-sharing.
 * when a class has an upperlimit, the fit-समय is computed from the
 * upperlimit service curve.  the link-sharing scheduler करोes not schedule
 * a class whose fit-समय exceeds the current समय.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/compiler.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/init.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <यंत्र/भाग64.h>

/*
 * kernel पूर्णांकernal service curve representation:
 *   coordinates are given by 64 bit अचिन्हित पूर्णांकegers.
 *   x-axis: unit is घड़ी count.
 *   y-axis: unit is byte.
 *
 *   The service curve parameters are converted to the पूर्णांकernal
 *   representation. The slope values are scaled to aव्योम overflow.
 *   the inverse slope values as well as the y-projection of the 1st
 *   segment are kept in order to aव्योम 64-bit भागide operations
 *   that are expensive on 32-bit architectures.
 */

काष्ठा पूर्णांकernal_sc अणु
	u64	sm1;	/* scaled slope of the 1st segment */
	u64	ism1;	/* scaled inverse-slope of the 1st segment */
	u64	dx;	/* the x-projection of the 1st segment */
	u64	dy;	/* the y-projection of the 1st segment */
	u64	sm2;	/* scaled slope of the 2nd segment */
	u64	ism2;	/* scaled inverse-slope of the 2nd segment */
पूर्ण;

/* runसमय service curve */
काष्ठा runसमय_sc अणु
	u64	x;	/* current starting position on x-axis */
	u64	y;	/* current starting position on y-axis */
	u64	sm1;	/* scaled slope of the 1st segment */
	u64	ism1;	/* scaled inverse-slope of the 1st segment */
	u64	dx;	/* the x-projection of the 1st segment */
	u64	dy;	/* the y-projection of the 1st segment */
	u64	sm2;	/* scaled slope of the 2nd segment */
	u64	ism2;	/* scaled inverse-slope of the 2nd segment */
पूर्ण;

क्रमागत hfsc_class_flags अणु
	HFSC_RSC = 0x1,
	HFSC_FSC = 0x2,
	HFSC_USC = 0x4
पूर्ण;

काष्ठा hfsc_class अणु
	काष्ठा Qdisc_class_common cl_common;

	काष्ठा gnet_stats_basic_packed bstats;
	काष्ठा gnet_stats_queue qstats;
	काष्ठा net_rate_estimator __rcu *rate_est;
	काष्ठा tcf_proto __rcu *filter_list; /* filter list */
	काष्ठा tcf_block *block;
	अचिन्हित पूर्णांक	filter_cnt;	/* filter count */
	अचिन्हित पूर्णांक	level;		/* class level in hierarchy */

	काष्ठा hfsc_sched *sched;	/* scheduler data */
	काष्ठा hfsc_class *cl_parent;	/* parent class */
	काष्ठा list_head siblings;	/* sibling classes */
	काष्ठा list_head children;	/* child classes */
	काष्ठा Qdisc	*qdisc;		/* leaf qdisc */

	काष्ठा rb_node el_node;		/* qdisc's eligible tree member */
	काष्ठा rb_root vt_tree;		/* active children sorted by cl_vt */
	काष्ठा rb_node vt_node;		/* parent's vt_tree member */
	काष्ठा rb_root cf_tree;		/* active children sorted by cl_f */
	काष्ठा rb_node cf_node;		/* parent's cf_heap member */

	u64	cl_total;		/* total work in bytes */
	u64	cl_cumul;		/* cumulative work in bytes करोne by
					   real-समय criteria */

	u64	cl_d;			/* deadline*/
	u64	cl_e;			/* eligible समय */
	u64	cl_vt;			/* भव समय */
	u64	cl_f;			/* समय when this class will fit क्रम
					   link-sharing, max(myf, cfmin) */
	u64	cl_myf;			/* my fit-समय (calculated from this
					   class's own upperlimit curve) */
	u64	cl_cfmin;		/* earliest children's fit-समय (used
					   with cl_myf to obtain cl_f) */
	u64	cl_cvपंचांगin;		/* minimal भव समय among the
					   children fit क्रम link-sharing
					   (monotonic within a period) */
	u64	cl_vtadj;		/* पूर्णांकra-period cumulative vt
					   adjusपंचांगent */
	u64	cl_cvtoff;		/* largest भव समय seen among
					   the children */

	काष्ठा पूर्णांकernal_sc cl_rsc;	/* पूर्णांकernal real-समय service curve */
	काष्ठा पूर्णांकernal_sc cl_fsc;	/* पूर्णांकernal fair service curve */
	काष्ठा पूर्णांकernal_sc cl_usc;	/* पूर्णांकernal upperlimit service curve */
	काष्ठा runसमय_sc cl_deadline;	/* deadline curve */
	काष्ठा runसमय_sc cl_eligible;	/* eligible curve */
	काष्ठा runसमय_sc cl_भव;	/* भव curve */
	काष्ठा runसमय_sc cl_ulimit;	/* upperlimit curve */

	u8		cl_flags;	/* which curves are valid */
	u32		cl_vtperiod;	/* vt period sequence number */
	u32		cl_parentperiod;/* parent's vt period sequence number*/
	u32		cl_nactive;	/* number of active children */
पूर्ण;

काष्ठा hfsc_sched अणु
	u16	defcls;				/* शेष class id */
	काष्ठा hfsc_class root;			/* root class */
	काष्ठा Qdisc_class_hash clhash;		/* class hash */
	काष्ठा rb_root eligible;		/* eligible tree */
	काष्ठा qdisc_watchकरोg watchकरोg;		/* watchकरोg समयr */
पूर्ण;

#घोषणा	HT_अनन्त	0xffffffffffffffffULL	/* infinite समय value */


/*
 * eligible tree holds backlogged classes being sorted by their eligible बार.
 * there is one eligible tree per hfsc instance.
 */

अटल व्योम
eltree_insert(काष्ठा hfsc_class *cl)
अणु
	काष्ठा rb_node **p = &cl->sched->eligible.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hfsc_class *cl1;

	जबतक (*p != शून्य) अणु
		parent = *p;
		cl1 = rb_entry(parent, काष्ठा hfsc_class, el_node);
		अगर (cl->cl_e >= cl1->cl_e)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण
	rb_link_node(&cl->el_node, parent, p);
	rb_insert_color(&cl->el_node, &cl->sched->eligible);
पूर्ण

अटल अंतरभूत व्योम
eltree_हटाओ(काष्ठा hfsc_class *cl)
अणु
	rb_erase(&cl->el_node, &cl->sched->eligible);
पूर्ण

अटल अंतरभूत व्योम
eltree_update(काष्ठा hfsc_class *cl)
अणु
	eltree_हटाओ(cl);
	eltree_insert(cl);
पूर्ण

/* find the class with the minimum deadline among the eligible classes */
अटल अंतरभूत काष्ठा hfsc_class *
eltree_get_mindl(काष्ठा hfsc_sched *q, u64 cur_समय)
अणु
	काष्ठा hfsc_class *p, *cl = शून्य;
	काष्ठा rb_node *n;

	क्रम (n = rb_first(&q->eligible); n != शून्य; n = rb_next(n)) अणु
		p = rb_entry(n, काष्ठा hfsc_class, el_node);
		अगर (p->cl_e > cur_समय)
			अवरोध;
		अगर (cl == शून्य || p->cl_d < cl->cl_d)
			cl = p;
	पूर्ण
	वापस cl;
पूर्ण

/* find the class with minimum eligible समय among the eligible classes */
अटल अंतरभूत काष्ठा hfsc_class *
eltree_get_minel(काष्ठा hfsc_sched *q)
अणु
	काष्ठा rb_node *n;

	n = rb_first(&q->eligible);
	अगर (n == शून्य)
		वापस शून्य;
	वापस rb_entry(n, काष्ठा hfsc_class, el_node);
पूर्ण

/*
 * vttree holds holds backlogged child classes being sorted by their भव
 * समय. each पूर्णांकermediate class has one vttree.
 */
अटल व्योम
vttree_insert(काष्ठा hfsc_class *cl)
अणु
	काष्ठा rb_node **p = &cl->cl_parent->vt_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hfsc_class *cl1;

	जबतक (*p != शून्य) अणु
		parent = *p;
		cl1 = rb_entry(parent, काष्ठा hfsc_class, vt_node);
		अगर (cl->cl_vt >= cl1->cl_vt)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण
	rb_link_node(&cl->vt_node, parent, p);
	rb_insert_color(&cl->vt_node, &cl->cl_parent->vt_tree);
पूर्ण

अटल अंतरभूत व्योम
vttree_हटाओ(काष्ठा hfsc_class *cl)
अणु
	rb_erase(&cl->vt_node, &cl->cl_parent->vt_tree);
पूर्ण

अटल अंतरभूत व्योम
vttree_update(काष्ठा hfsc_class *cl)
अणु
	vttree_हटाओ(cl);
	vttree_insert(cl);
पूर्ण

अटल अंतरभूत काष्ठा hfsc_class *
vttree_firstfit(काष्ठा hfsc_class *cl, u64 cur_समय)
अणु
	काष्ठा hfsc_class *p;
	काष्ठा rb_node *n;

	क्रम (n = rb_first(&cl->vt_tree); n != शून्य; n = rb_next(n)) अणु
		p = rb_entry(n, काष्ठा hfsc_class, vt_node);
		अगर (p->cl_f <= cur_समय)
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * get the leaf class with the minimum vt in the hierarchy
 */
अटल काष्ठा hfsc_class *
vttree_get_minvt(काष्ठा hfsc_class *cl, u64 cur_समय)
अणु
	/* अगर root-class's cfmin is bigger than cur_समय nothing to करो */
	अगर (cl->cl_cfmin > cur_समय)
		वापस शून्य;

	जबतक (cl->level > 0) अणु
		cl = vttree_firstfit(cl, cur_समय);
		अगर (cl == शून्य)
			वापस शून्य;
		/*
		 * update parent's cl_cvपंचांगin.
		 */
		अगर (cl->cl_parent->cl_cvपंचांगin < cl->cl_vt)
			cl->cl_parent->cl_cvपंचांगin = cl->cl_vt;
	पूर्ण
	वापस cl;
पूर्ण

अटल व्योम
cftree_insert(काष्ठा hfsc_class *cl)
अणु
	काष्ठा rb_node **p = &cl->cl_parent->cf_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hfsc_class *cl1;

	जबतक (*p != शून्य) अणु
		parent = *p;
		cl1 = rb_entry(parent, काष्ठा hfsc_class, cf_node);
		अगर (cl->cl_f >= cl1->cl_f)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण
	rb_link_node(&cl->cf_node, parent, p);
	rb_insert_color(&cl->cf_node, &cl->cl_parent->cf_tree);
पूर्ण

अटल अंतरभूत व्योम
cftree_हटाओ(काष्ठा hfsc_class *cl)
अणु
	rb_erase(&cl->cf_node, &cl->cl_parent->cf_tree);
पूर्ण

अटल अंतरभूत व्योम
cftree_update(काष्ठा hfsc_class *cl)
अणु
	cftree_हटाओ(cl);
	cftree_insert(cl);
पूर्ण

/*
 * service curve support functions
 *
 *  बाह्यal service curve parameters
 *	m: bps
 *	d: us
 *  पूर्णांकernal service curve parameters
 *	sm: (bytes/psched_us) << SM_SHIFT
 *	ism: (psched_us/byte) << ISM_SHIFT
 *	dx: psched_us
 *
 * The घड़ी source resolution with kसमय and PSCHED_SHIFT 10 is 1.024us.
 *
 * sm and ism are scaled in order to keep effective digits.
 * SM_SHIFT and ISM_SHIFT are selected to keep at least 4 effective
 * digits in decimal using the following table.
 *
 *  bits/sec      100Kbps     1Mbps     10Mbps     100Mbps    1Gbps
 *  ------------+-------------------------------------------------------
 *  bytes/1.024us 12.8e-3    128e-3     1280e-3    12800e-3   128000e-3
 *
 *  1.024us/byte  78.125     7.8125     0.78125    0.078125   0.0078125
 *
 * So, क्रम PSCHED_SHIFT 10 we need: SM_SHIFT 20, ISM_SHIFT 18.
 */
#घोषणा	SM_SHIFT	(30 - PSCHED_SHIFT)
#घोषणा	ISM_SHIFT	(8 + PSCHED_SHIFT)

#घोषणा	SM_MASK		((1ULL << SM_SHIFT) - 1)
#घोषणा	ISM_MASK	((1ULL << ISM_SHIFT) - 1)

अटल अंतरभूत u64
seg_x2y(u64 x, u64 sm)
अणु
	u64 y;

	/*
	 * compute
	 *	y = x * sm >> SM_SHIFT
	 * but भागide it क्रम the upper and lower bits to aव्योम overflow
	 */
	y = (x >> SM_SHIFT) * sm + (((x & SM_MASK) * sm) >> SM_SHIFT);
	वापस y;
पूर्ण

अटल अंतरभूत u64
seg_y2x(u64 y, u64 ism)
अणु
	u64 x;

	अगर (y == 0)
		x = 0;
	अन्यथा अगर (ism == HT_अनन्त)
		x = HT_अनन्त;
	अन्यथा अणु
		x = (y >> ISM_SHIFT) * ism
		    + (((y & ISM_MASK) * ism) >> ISM_SHIFT);
	पूर्ण
	वापस x;
पूर्ण

/* Convert m (bps) पूर्णांकo sm (bytes/psched us) */
अटल u64
m2sm(u32 m)
अणु
	u64 sm;

	sm = ((u64)m << SM_SHIFT);
	sm += PSCHED_TICKS_PER_SEC - 1;
	करो_भाग(sm, PSCHED_TICKS_PER_SEC);
	वापस sm;
पूर्ण

/* convert m (bps) पूर्णांकo ism (psched us/byte) */
अटल u64
m2ism(u32 m)
अणु
	u64 ism;

	अगर (m == 0)
		ism = HT_अनन्त;
	अन्यथा अणु
		ism = ((u64)PSCHED_TICKS_PER_SEC << ISM_SHIFT);
		ism += m - 1;
		करो_भाग(ism, m);
	पूर्ण
	वापस ism;
पूर्ण

/* convert d (us) पूर्णांकo dx (psched us) */
अटल u64
d2dx(u32 d)
अणु
	u64 dx;

	dx = ((u64)d * PSCHED_TICKS_PER_SEC);
	dx += USEC_PER_SEC - 1;
	करो_भाग(dx, USEC_PER_SEC);
	वापस dx;
पूर्ण

/* convert sm (bytes/psched us) पूर्णांकo m (bps) */
अटल u32
sm2m(u64 sm)
अणु
	u64 m;

	m = (sm * PSCHED_TICKS_PER_SEC) >> SM_SHIFT;
	वापस (u32)m;
पूर्ण

/* convert dx (psched us) पूर्णांकo d (us) */
अटल u32
dx2d(u64 dx)
अणु
	u64 d;

	d = dx * USEC_PER_SEC;
	करो_भाग(d, PSCHED_TICKS_PER_SEC);
	वापस (u32)d;
पूर्ण

अटल व्योम
sc2isc(काष्ठा tc_service_curve *sc, काष्ठा पूर्णांकernal_sc *isc)
अणु
	isc->sm1  = m2sm(sc->m1);
	isc->ism1 = m2ism(sc->m1);
	isc->dx   = d2dx(sc->d);
	isc->dy   = seg_x2y(isc->dx, isc->sm1);
	isc->sm2  = m2sm(sc->m2);
	isc->ism2 = m2ism(sc->m2);
पूर्ण

/*
 * initialize the runसमय service curve with the given पूर्णांकernal
 * service curve starting at (x, y).
 */
अटल व्योम
rtsc_init(काष्ठा runसमय_sc *rtsc, काष्ठा पूर्णांकernal_sc *isc, u64 x, u64 y)
अणु
	rtsc->x	   = x;
	rtsc->y    = y;
	rtsc->sm1  = isc->sm1;
	rtsc->ism1 = isc->ism1;
	rtsc->dx   = isc->dx;
	rtsc->dy   = isc->dy;
	rtsc->sm2  = isc->sm2;
	rtsc->ism2 = isc->ism2;
पूर्ण

/*
 * calculate the y-projection of the runसमय service curve by the
 * given x-projection value
 */
अटल u64
rtsc_y2x(काष्ठा runसमय_sc *rtsc, u64 y)
अणु
	u64 x;

	अगर (y < rtsc->y)
		x = rtsc->x;
	अन्यथा अगर (y <= rtsc->y + rtsc->dy) अणु
		/* x beदीर्घs to the 1st segment */
		अगर (rtsc->dy == 0)
			x = rtsc->x + rtsc->dx;
		अन्यथा
			x = rtsc->x + seg_y2x(y - rtsc->y, rtsc->ism1);
	पूर्ण अन्यथा अणु
		/* x beदीर्घs to the 2nd segment */
		x = rtsc->x + rtsc->dx
		    + seg_y2x(y - rtsc->y - rtsc->dy, rtsc->ism2);
	पूर्ण
	वापस x;
पूर्ण

अटल u64
rtsc_x2y(काष्ठा runसमय_sc *rtsc, u64 x)
अणु
	u64 y;

	अगर (x <= rtsc->x)
		y = rtsc->y;
	अन्यथा अगर (x <= rtsc->x + rtsc->dx)
		/* y beदीर्घs to the 1st segment */
		y = rtsc->y + seg_x2y(x - rtsc->x, rtsc->sm1);
	अन्यथा
		/* y beदीर्घs to the 2nd segment */
		y = rtsc->y + rtsc->dy
		    + seg_x2y(x - rtsc->x - rtsc->dx, rtsc->sm2);
	वापस y;
पूर्ण

/*
 * update the runसमय service curve by taking the minimum of the current
 * runसमय service curve and the service curve starting at (x, y).
 */
अटल व्योम
rtsc_min(काष्ठा runसमय_sc *rtsc, काष्ठा पूर्णांकernal_sc *isc, u64 x, u64 y)
अणु
	u64 y1, y2, dx, dy;
	u32 dsm;

	अगर (isc->sm1 <= isc->sm2) अणु
		/* service curve is convex */
		y1 = rtsc_x2y(rtsc, x);
		अगर (y1 < y)
			/* the current rtsc is smaller */
			वापस;
		rtsc->x = x;
		rtsc->y = y;
		वापस;
	पूर्ण

	/*
	 * service curve is concave
	 * compute the two y values of the current rtsc
	 *	y1: at x
	 *	y2: at (x + dx)
	 */
	y1 = rtsc_x2y(rtsc, x);
	अगर (y1 <= y) अणु
		/* rtsc is below isc, no change to rtsc */
		वापस;
	पूर्ण

	y2 = rtsc_x2y(rtsc, x + isc->dx);
	अगर (y2 >= y + isc->dy) अणु
		/* rtsc is above isc, replace rtsc by isc */
		rtsc->x = x;
		rtsc->y = y;
		rtsc->dx = isc->dx;
		rtsc->dy = isc->dy;
		वापस;
	पूर्ण

	/*
	 * the two curves पूर्णांकersect
	 * compute the offsets (dx, dy) using the reverse
	 * function of seg_x2y()
	 *	seg_x2y(dx, sm1) == seg_x2y(dx, sm2) + (y1 - y)
	 */
	dx = (y1 - y) << SM_SHIFT;
	dsm = isc->sm1 - isc->sm2;
	करो_भाग(dx, dsm);
	/*
	 * check अगर (x, y1) beदीर्घs to the 1st segment of rtsc.
	 * अगर so, add the offset.
	 */
	अगर (rtsc->x + rtsc->dx > x)
		dx += rtsc->x + rtsc->dx - x;
	dy = seg_x2y(dx, isc->sm1);

	rtsc->x = x;
	rtsc->y = y;
	rtsc->dx = dx;
	rtsc->dy = dy;
पूर्ण

अटल व्योम
init_ed(काष्ठा hfsc_class *cl, अचिन्हित पूर्णांक next_len)
अणु
	u64 cur_समय = psched_get_समय();

	/* update the deadline curve */
	rtsc_min(&cl->cl_deadline, &cl->cl_rsc, cur_समय, cl->cl_cumul);

	/*
	 * update the eligible curve.
	 * क्रम concave, it is equal to the deadline curve.
	 * क्रम convex, it is a linear curve with slope m2.
	 */
	cl->cl_eligible = cl->cl_deadline;
	अगर (cl->cl_rsc.sm1 <= cl->cl_rsc.sm2) अणु
		cl->cl_eligible.dx = 0;
		cl->cl_eligible.dy = 0;
	पूर्ण

	/* compute e and d */
	cl->cl_e = rtsc_y2x(&cl->cl_eligible, cl->cl_cumul);
	cl->cl_d = rtsc_y2x(&cl->cl_deadline, cl->cl_cumul + next_len);

	eltree_insert(cl);
पूर्ण

अटल व्योम
update_ed(काष्ठा hfsc_class *cl, अचिन्हित पूर्णांक next_len)
अणु
	cl->cl_e = rtsc_y2x(&cl->cl_eligible, cl->cl_cumul);
	cl->cl_d = rtsc_y2x(&cl->cl_deadline, cl->cl_cumul + next_len);

	eltree_update(cl);
पूर्ण

अटल अंतरभूत व्योम
update_d(काष्ठा hfsc_class *cl, अचिन्हित पूर्णांक next_len)
अणु
	cl->cl_d = rtsc_y2x(&cl->cl_deadline, cl->cl_cumul + next_len);
पूर्ण

अटल अंतरभूत व्योम
update_cfmin(काष्ठा hfsc_class *cl)
अणु
	काष्ठा rb_node *n = rb_first(&cl->cf_tree);
	काष्ठा hfsc_class *p;

	अगर (n == शून्य) अणु
		cl->cl_cfmin = 0;
		वापस;
	पूर्ण
	p = rb_entry(n, काष्ठा hfsc_class, cf_node);
	cl->cl_cfmin = p->cl_f;
पूर्ण

अटल व्योम
init_vf(काष्ठा hfsc_class *cl, अचिन्हित पूर्णांक len)
अणु
	काष्ठा hfsc_class *max_cl;
	काष्ठा rb_node *n;
	u64 vt, f, cur_समय;
	पूर्णांक go_active;

	cur_समय = 0;
	go_active = 1;
	क्रम (; cl->cl_parent != शून्य; cl = cl->cl_parent) अणु
		अगर (go_active && cl->cl_nactive++ == 0)
			go_active = 1;
		अन्यथा
			go_active = 0;

		अगर (go_active) अणु
			n = rb_last(&cl->cl_parent->vt_tree);
			अगर (n != शून्य) अणु
				max_cl = rb_entry(n, काष्ठा hfsc_class, vt_node);
				/*
				 * set vt to the average of the min and max
				 * classes.  अगर the parent's period didn't
				 * change, करोn't decrease vt of the class.
				 */
				vt = max_cl->cl_vt;
				अगर (cl->cl_parent->cl_cvपंचांगin != 0)
					vt = (cl->cl_parent->cl_cvपंचांगin + vt)/2;

				अगर (cl->cl_parent->cl_vtperiod !=
				    cl->cl_parentperiod || vt > cl->cl_vt)
					cl->cl_vt = vt;
			पूर्ण अन्यथा अणु
				/*
				 * first child क्रम a new parent backlog period.
				 * initialize cl_vt to the highest value seen
				 * among the siblings. this is analogous to
				 * what cur_समय would provide in realसमय हाल.
				 */
				cl->cl_vt = cl->cl_parent->cl_cvtoff;
				cl->cl_parent->cl_cvपंचांगin = 0;
			पूर्ण

			/* update the भव curve */
			rtsc_min(&cl->cl_भव, &cl->cl_fsc, cl->cl_vt, cl->cl_total);
			cl->cl_vtadj = 0;

			cl->cl_vtperiod++;  /* increment vt period */
			cl->cl_parentperiod = cl->cl_parent->cl_vtperiod;
			अगर (cl->cl_parent->cl_nactive == 0)
				cl->cl_parentperiod++;
			cl->cl_f = 0;

			vttree_insert(cl);
			cftree_insert(cl);

			अगर (cl->cl_flags & HFSC_USC) अणु
				/* class has upper limit curve */
				अगर (cur_समय == 0)
					cur_समय = psched_get_समय();

				/* update the ulimit curve */
				rtsc_min(&cl->cl_ulimit, &cl->cl_usc, cur_समय,
					 cl->cl_total);
				/* compute myf */
				cl->cl_myf = rtsc_y2x(&cl->cl_ulimit,
						      cl->cl_total);
			पूर्ण
		पूर्ण

		f = max(cl->cl_myf, cl->cl_cfmin);
		अगर (f != cl->cl_f) अणु
			cl->cl_f = f;
			cftree_update(cl);
		पूर्ण
		update_cfmin(cl->cl_parent);
	पूर्ण
पूर्ण

अटल व्योम
update_vf(काष्ठा hfsc_class *cl, अचिन्हित पूर्णांक len, u64 cur_समय)
अणु
	u64 f; /* , myf_bound, delta; */
	पूर्णांक go_passive = 0;

	अगर (cl->qdisc->q.qlen == 0 && cl->cl_flags & HFSC_FSC)
		go_passive = 1;

	क्रम (; cl->cl_parent != शून्य; cl = cl->cl_parent) अणु
		cl->cl_total += len;

		अगर (!(cl->cl_flags & HFSC_FSC) || cl->cl_nactive == 0)
			जारी;

		अगर (go_passive && --cl->cl_nactive == 0)
			go_passive = 1;
		अन्यथा
			go_passive = 0;

		/* update vt */
		cl->cl_vt = rtsc_y2x(&cl->cl_भव, cl->cl_total) + cl->cl_vtadj;

		/*
		 * अगर vt of the class is smaller than cvपंचांगin,
		 * the class was skipped in the past due to non-fit.
		 * अगर so, we need to adjust vtadj.
		 */
		अगर (cl->cl_vt < cl->cl_parent->cl_cvपंचांगin) अणु
			cl->cl_vtadj += cl->cl_parent->cl_cvपंचांगin - cl->cl_vt;
			cl->cl_vt = cl->cl_parent->cl_cvपंचांगin;
		पूर्ण

		अगर (go_passive) अणु
			/* no more active child, going passive */

			/* update cvtoff of the parent class */
			अगर (cl->cl_vt > cl->cl_parent->cl_cvtoff)
				cl->cl_parent->cl_cvtoff = cl->cl_vt;

			/* हटाओ this class from the vt tree */
			vttree_हटाओ(cl);

			cftree_हटाओ(cl);
			update_cfmin(cl->cl_parent);

			जारी;
		पूर्ण

		/* update the vt tree */
		vttree_update(cl);

		/* update f */
		अगर (cl->cl_flags & HFSC_USC) अणु
			cl->cl_myf = rtsc_y2x(&cl->cl_ulimit, cl->cl_total);
#अगर 0
			cl->cl_myf = cl->cl_myfadj + rtsc_y2x(&cl->cl_ulimit,
							      cl->cl_total);
			/*
			 * This code causes classes to stay way under their
			 * limit when multiple classes are used at gigabit
			 * speed. needs investigation. -kaber
			 */
			/*
			 * अगर myf lags behind by more than one घड़ी tick
			 * from the current समय, adjust myfadj to prevent
			 * a rate-limited class from going greedy.
			 * in a steady state under rate-limiting, myf
			 * fluctuates within one घड़ी tick.
			 */
			myf_bound = cur_समय - PSCHED_JIFFIE2US(1);
			अगर (cl->cl_myf < myf_bound) अणु
				delta = cur_समय - cl->cl_myf;
				cl->cl_myfadj += delta;
				cl->cl_myf += delta;
			पूर्ण
#पूर्ण_अगर
		पूर्ण

		f = max(cl->cl_myf, cl->cl_cfmin);
		अगर (f != cl->cl_f) अणु
			cl->cl_f = f;
			cftree_update(cl);
			update_cfmin(cl->cl_parent);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
qdisc_peek_len(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;

	skb = sch->ops->peek(sch);
	अगर (unlikely(skb == शून्य)) अणु
		qdisc_warn_nonwc("qdisc_peek_len", sch);
		वापस 0;
	पूर्ण
	len = qdisc_pkt_len(skb);

	वापस len;
पूर्ण

अटल व्योम
hfsc_adjust_levels(काष्ठा hfsc_class *cl)
अणु
	काष्ठा hfsc_class *p;
	अचिन्हित पूर्णांक level;

	करो अणु
		level = 0;
		list_क्रम_each_entry(p, &cl->children, siblings) अणु
			अगर (p->level >= level)
				level = p->level + 1;
		पूर्ण
		cl->level = level;
	पूर्ण जबतक ((cl = cl->cl_parent) != शून्य);
पूर्ण

अटल अंतरभूत काष्ठा hfsc_class *
hfsc_find_class(u32 classid, काष्ठा Qdisc *sch)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा Qdisc_class_common *clc;

	clc = qdisc_class_find(&q->clhash, classid);
	अगर (clc == शून्य)
		वापस शून्य;
	वापस container_of(clc, काष्ठा hfsc_class, cl_common);
पूर्ण

अटल व्योम
hfsc_change_rsc(काष्ठा hfsc_class *cl, काष्ठा tc_service_curve *rsc,
		u64 cur_समय)
अणु
	sc2isc(rsc, &cl->cl_rsc);
	rtsc_init(&cl->cl_deadline, &cl->cl_rsc, cur_समय, cl->cl_cumul);
	cl->cl_eligible = cl->cl_deadline;
	अगर (cl->cl_rsc.sm1 <= cl->cl_rsc.sm2) अणु
		cl->cl_eligible.dx = 0;
		cl->cl_eligible.dy = 0;
	पूर्ण
	cl->cl_flags |= HFSC_RSC;
पूर्ण

अटल व्योम
hfsc_change_fsc(काष्ठा hfsc_class *cl, काष्ठा tc_service_curve *fsc)
अणु
	sc2isc(fsc, &cl->cl_fsc);
	rtsc_init(&cl->cl_भव, &cl->cl_fsc, cl->cl_vt, cl->cl_total);
	cl->cl_flags |= HFSC_FSC;
पूर्ण

अटल व्योम
hfsc_change_usc(काष्ठा hfsc_class *cl, काष्ठा tc_service_curve *usc,
		u64 cur_समय)
अणु
	sc2isc(usc, &cl->cl_usc);
	rtsc_init(&cl->cl_ulimit, &cl->cl_usc, cur_समय, cl->cl_total);
	cl->cl_flags |= HFSC_USC;
पूर्ण

अटल स्थिर काष्ठा nla_policy hfsc_policy[TCA_HFSC_MAX + 1] = अणु
	[TCA_HFSC_RSC]	= अणु .len = माप(काष्ठा tc_service_curve) पूर्ण,
	[TCA_HFSC_FSC]	= अणु .len = माप(काष्ठा tc_service_curve) पूर्ण,
	[TCA_HFSC_USC]	= अणु .len = माप(काष्ठा tc_service_curve) पूर्ण,
पूर्ण;

अटल पूर्णांक
hfsc_change_class(काष्ठा Qdisc *sch, u32 classid, u32 parentid,
		  काष्ठा nlattr **tca, अचिन्हित दीर्घ *arg,
		  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा hfsc_class *cl = (काष्ठा hfsc_class *)*arg;
	काष्ठा hfsc_class *parent = शून्य;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_HFSC_MAX + 1];
	काष्ठा tc_service_curve *rsc = शून्य, *fsc = शून्य, *usc = शून्य;
	u64 cur_समय;
	पूर्णांक err;

	अगर (opt == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_HFSC_MAX, opt, hfsc_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_HFSC_RSC]) अणु
		rsc = nla_data(tb[TCA_HFSC_RSC]);
		अगर (rsc->m1 == 0 && rsc->m2 == 0)
			rsc = शून्य;
	पूर्ण

	अगर (tb[TCA_HFSC_FSC]) अणु
		fsc = nla_data(tb[TCA_HFSC_FSC]);
		अगर (fsc->m1 == 0 && fsc->m2 == 0)
			fsc = शून्य;
	पूर्ण

	अगर (tb[TCA_HFSC_USC]) अणु
		usc = nla_data(tb[TCA_HFSC_USC]);
		अगर (usc->m1 == 0 && usc->m2 == 0)
			usc = शून्य;
	पूर्ण

	अगर (cl != शून्य) अणु
		पूर्णांक old_flags;

		अगर (parentid) अणु
			अगर (cl->cl_parent &&
			    cl->cl_parent->cl_common.classid != parentid)
				वापस -EINVAL;
			अगर (cl->cl_parent == शून्य && parentid != TC_H_ROOT)
				वापस -EINVAL;
		पूर्ण
		cur_समय = psched_get_समय();

		अगर (tca[TCA_RATE]) अणु
			err = gen_replace_estimator(&cl->bstats, शून्य,
						    &cl->rate_est,
						    शून्य,
						    qdisc_root_sleeping_running(sch),
						    tca[TCA_RATE]);
			अगर (err)
				वापस err;
		पूर्ण

		sch_tree_lock(sch);
		old_flags = cl->cl_flags;

		अगर (rsc != शून्य)
			hfsc_change_rsc(cl, rsc, cur_समय);
		अगर (fsc != शून्य)
			hfsc_change_fsc(cl, fsc);
		अगर (usc != शून्य)
			hfsc_change_usc(cl, usc, cur_समय);

		अगर (cl->qdisc->q.qlen != 0) अणु
			पूर्णांक len = qdisc_peek_len(cl->qdisc);

			अगर (cl->cl_flags & HFSC_RSC) अणु
				अगर (old_flags & HFSC_RSC)
					update_ed(cl, len);
				अन्यथा
					init_ed(cl, len);
			पूर्ण

			अगर (cl->cl_flags & HFSC_FSC) अणु
				अगर (old_flags & HFSC_FSC)
					update_vf(cl, 0, cur_समय);
				अन्यथा
					init_vf(cl, len);
			पूर्ण
		पूर्ण
		sch_tree_unlock(sch);

		वापस 0;
	पूर्ण

	अगर (parentid == TC_H_ROOT)
		वापस -EEXIST;

	parent = &q->root;
	अगर (parentid) अणु
		parent = hfsc_find_class(parentid, sch);
		अगर (parent == शून्य)
			वापस -ENOENT;
	पूर्ण

	अगर (classid == 0 || TC_H_MAJ(classid ^ sch->handle) != 0)
		वापस -EINVAL;
	अगर (hfsc_find_class(classid, sch))
		वापस -EEXIST;

	अगर (rsc == शून्य && fsc == शून्य)
		वापस -EINVAL;

	cl = kzalloc(माप(काष्ठा hfsc_class), GFP_KERNEL);
	अगर (cl == शून्य)
		वापस -ENOBUFS;

	err = tcf_block_get(&cl->block, &cl->filter_list, sch, extack);
	अगर (err) अणु
		kमुक्त(cl);
		वापस err;
	पूर्ण

	अगर (tca[TCA_RATE]) अणु
		err = gen_new_estimator(&cl->bstats, शून्य, &cl->rate_est,
					शून्य,
					qdisc_root_sleeping_running(sch),
					tca[TCA_RATE]);
		अगर (err) अणु
			tcf_block_put(cl->block);
			kमुक्त(cl);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (rsc != शून्य)
		hfsc_change_rsc(cl, rsc, 0);
	अगर (fsc != शून्य)
		hfsc_change_fsc(cl, fsc);
	अगर (usc != शून्य)
		hfsc_change_usc(cl, usc, 0);

	cl->cl_common.classid = classid;
	cl->sched     = q;
	cl->cl_parent = parent;
	cl->qdisc = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
				      classid, शून्य);
	अगर (cl->qdisc == शून्य)
		cl->qdisc = &noop_qdisc;
	अन्यथा
		qdisc_hash_add(cl->qdisc, true);
	INIT_LIST_HEAD(&cl->children);
	cl->vt_tree = RB_ROOT;
	cl->cf_tree = RB_ROOT;

	sch_tree_lock(sch);
	qdisc_class_hash_insert(&q->clhash, &cl->cl_common);
	list_add_tail(&cl->siblings, &parent->children);
	अगर (parent->level == 0)
		qdisc_purge_queue(parent->qdisc);
	hfsc_adjust_levels(parent);
	sch_tree_unlock(sch);

	qdisc_class_hash_grow(sch, &q->clhash);

	*arg = (अचिन्हित दीर्घ)cl;
	वापस 0;
पूर्ण

अटल व्योम
hfsc_destroy_class(काष्ठा Qdisc *sch, काष्ठा hfsc_class *cl)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);

	tcf_block_put(cl->block);
	qdisc_put(cl->qdisc);
	gen_समाप्त_estimator(&cl->rate_est);
	अगर (cl != &q->root)
		kमुक्त(cl);
पूर्ण

अटल पूर्णांक
hfsc_delete_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
		  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा hfsc_class *cl = (काष्ठा hfsc_class *)arg;

	अगर (cl->level > 0 || cl->filter_cnt > 0 || cl == &q->root)
		वापस -EBUSY;

	sch_tree_lock(sch);

	list_del(&cl->siblings);
	hfsc_adjust_levels(cl->cl_parent);

	qdisc_purge_queue(cl->qdisc);
	qdisc_class_hash_हटाओ(&q->clhash, &cl->cl_common);

	sch_tree_unlock(sch);

	hfsc_destroy_class(sch, cl);
	वापस 0;
पूर्ण

अटल काष्ठा hfsc_class *
hfsc_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch, पूर्णांक *qerr)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा hfsc_class *head, *cl;
	काष्ठा tcf_result res;
	काष्ठा tcf_proto *tcf;
	पूर्णांक result;

	अगर (TC_H_MAJ(skb->priority ^ sch->handle) == 0 &&
	    (cl = hfsc_find_class(skb->priority, sch)) != शून्य)
		अगर (cl->level == 0)
			वापस cl;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	head = &q->root;
	tcf = rcu_dereference_bh(q->root.filter_list);
	जबतक (tcf && (result = tcf_classअगरy(skb, tcf, &res, false)) >= 0) अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (result) अणु
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			fallthrough;
		हाल TC_ACT_SHOT:
			वापस शून्य;
		पूर्ण
#पूर्ण_अगर
		cl = (काष्ठा hfsc_class *)res.class;
		अगर (!cl) अणु
			cl = hfsc_find_class(res.classid, sch);
			अगर (!cl)
				अवरोध; /* filter selected invalid classid */
			अगर (cl->level >= head->level)
				अवरोध; /* filter may only poपूर्णांक करोwnwards */
		पूर्ण

		अगर (cl->level == 0)
			वापस cl; /* hit leaf class */

		/* apply inner filter chain */
		tcf = rcu_dereference_bh(cl->filter_list);
		head = cl;
	पूर्ण

	/* classअगरication failed, try शेष class */
	cl = hfsc_find_class(TC_H_MAKE(TC_H_MAJ(sch->handle), q->defcls), sch);
	अगर (cl == शून्य || cl->level > 0)
		वापस शून्य;

	वापस cl;
पूर्ण

अटल पूर्णांक
hfsc_graft_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
		 काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hfsc_class *cl = (काष्ठा hfsc_class *)arg;

	अगर (cl->level > 0)
		वापस -EINVAL;
	अगर (new == शून्य) अणु
		new = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					cl->cl_common.classid, शून्य);
		अगर (new == शून्य)
			new = &noop_qdisc;
	पूर्ण

	*old = qdisc_replace(sch, new, &cl->qdisc);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *
hfsc_class_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hfsc_class *cl = (काष्ठा hfsc_class *)arg;

	अगर (cl->level == 0)
		वापस cl->qdisc;

	वापस शून्य;
पूर्ण

अटल व्योम
hfsc_qlen_notअगरy(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hfsc_class *cl = (काष्ठा hfsc_class *)arg;

	/* vttree is now handled in update_vf() so that update_vf(cl, 0, 0)
	 * needs to be called explicitly to हटाओ a class from vttree.
	 */
	update_vf(cl, 0, 0);
	अगर (cl->cl_flags & HFSC_RSC)
		eltree_हटाओ(cl);
पूर्ण

अटल अचिन्हित दीर्घ
hfsc_search_class(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस (अचिन्हित दीर्घ)hfsc_find_class(classid, sch);
पूर्ण

अटल अचिन्हित दीर्घ
hfsc_bind_tcf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent, u32 classid)
अणु
	काष्ठा hfsc_class *p = (काष्ठा hfsc_class *)parent;
	काष्ठा hfsc_class *cl = hfsc_find_class(classid, sch);

	अगर (cl != शून्य) अणु
		अगर (p != शून्य && p->level <= cl->level)
			वापस 0;
		cl->filter_cnt++;
	पूर्ण

	वापस (अचिन्हित दीर्घ)cl;
पूर्ण

अटल व्योम
hfsc_unbind_tcf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hfsc_class *cl = (काष्ठा hfsc_class *)arg;

	cl->filter_cnt--;
पूर्ण

अटल काष्ठा tcf_block *hfsc_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा hfsc_class *cl = (काष्ठा hfsc_class *)arg;

	अगर (cl == शून्य)
		cl = &q->root;

	वापस cl->block;
पूर्ण

अटल पूर्णांक
hfsc_dump_sc(काष्ठा sk_buff *skb, पूर्णांक attr, काष्ठा पूर्णांकernal_sc *sc)
अणु
	काष्ठा tc_service_curve tsc;

	tsc.m1 = sm2m(sc->sm1);
	tsc.d  = dx2d(sc->dx);
	tsc.m2 = sm2m(sc->sm2);
	अगर (nla_put(skb, attr, माप(tsc), &tsc))
		जाओ nla_put_failure;

	वापस skb->len;

 nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक
hfsc_dump_curves(काष्ठा sk_buff *skb, काष्ठा hfsc_class *cl)
अणु
	अगर ((cl->cl_flags & HFSC_RSC) &&
	    (hfsc_dump_sc(skb, TCA_HFSC_RSC, &cl->cl_rsc) < 0))
		जाओ nla_put_failure;

	अगर ((cl->cl_flags & HFSC_FSC) &&
	    (hfsc_dump_sc(skb, TCA_HFSC_FSC, &cl->cl_fsc) < 0))
		जाओ nla_put_failure;

	अगर ((cl->cl_flags & HFSC_USC) &&
	    (hfsc_dump_sc(skb, TCA_HFSC_USC, &cl->cl_usc) < 0))
		जाओ nla_put_failure;

	वापस skb->len;

 nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक
hfsc_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा sk_buff *skb,
		काष्ठा tcmsg *tcm)
अणु
	काष्ठा hfsc_class *cl = (काष्ठा hfsc_class *)arg;
	काष्ठा nlattr *nest;

	tcm->tcm_parent = cl->cl_parent ? cl->cl_parent->cl_common.classid :
					  TC_H_ROOT;
	tcm->tcm_handle = cl->cl_common.classid;
	अगर (cl->level == 0)
		tcm->tcm_info = cl->qdisc->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	अगर (hfsc_dump_curves(skb, cl) < 0)
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, nest);

 nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
hfsc_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
	काष्ठा gnet_dump *d)
अणु
	काष्ठा hfsc_class *cl = (काष्ठा hfsc_class *)arg;
	काष्ठा tc_hfsc_stats xstats;
	__u32 qlen;

	qdisc_qstats_qlen_backlog(cl->qdisc, &qlen, &cl->qstats.backlog);
	xstats.level   = cl->level;
	xstats.period  = cl->cl_vtperiod;
	xstats.work    = cl->cl_total;
	xstats.rtwork  = cl->cl_cumul;

	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch), d, शून्य, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, शून्य, &cl->qstats, qlen) < 0)
		वापस -1;

	वापस gnet_stats_copy_app(d, &xstats, माप(xstats));
पूर्ण



अटल व्योम
hfsc_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा hfsc_class *cl;
	अचिन्हित पूर्णांक i;

	अगर (arg->stop)
		वापस;

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[i],
				     cl_common.hnode) अणु
			अगर (arg->count < arg->skip) अणु
				arg->count++;
				जारी;
			पूर्ण
			अगर (arg->fn(sch, (अचिन्हित दीर्घ)cl, arg) < 0) अणु
				arg->stop = 1;
				वापस;
			पूर्ण
			arg->count++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
hfsc_schedule_watchकरोg(काष्ठा Qdisc *sch)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा hfsc_class *cl;
	u64 next_समय = 0;

	cl = eltree_get_minel(q);
	अगर (cl)
		next_समय = cl->cl_e;
	अगर (q->root.cl_cfmin != 0) अणु
		अगर (next_समय == 0 || next_समय > q->root.cl_cfmin)
			next_समय = q->root.cl_cfmin;
	पूर्ण
	अगर (next_समय)
		qdisc_watchकरोg_schedule(&q->watchकरोg, next_समय);
पूर्ण

अटल पूर्णांक
hfsc_init_qdisc(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा tc_hfsc_qopt *qopt;
	पूर्णांक err;

	qdisc_watchकरोg_init(&q->watchकरोg, sch);

	अगर (!opt || nla_len(opt) < माप(*qopt))
		वापस -EINVAL;
	qopt = nla_data(opt);

	q->defcls = qopt->defcls;
	err = qdisc_class_hash_init(&q->clhash);
	अगर (err < 0)
		वापस err;
	q->eligible = RB_ROOT;

	err = tcf_block_get(&q->root.block, &q->root.filter_list, sch, extack);
	अगर (err)
		वापस err;

	q->root.cl_common.classid = sch->handle;
	q->root.sched   = q;
	q->root.qdisc = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					  sch->handle, शून्य);
	अगर (q->root.qdisc == शून्य)
		q->root.qdisc = &noop_qdisc;
	अन्यथा
		qdisc_hash_add(q->root.qdisc, true);
	INIT_LIST_HEAD(&q->root.children);
	q->root.vt_tree = RB_ROOT;
	q->root.cf_tree = RB_ROOT;

	qdisc_class_hash_insert(&q->clhash, &q->root.cl_common);
	qdisc_class_hash_grow(sch, &q->clhash);

	वापस 0;
पूर्ण

अटल पूर्णांक
hfsc_change_qdisc(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा tc_hfsc_qopt *qopt;

	अगर (opt == शून्य || nla_len(opt) < माप(*qopt))
		वापस -EINVAL;
	qopt = nla_data(opt);

	sch_tree_lock(sch);
	q->defcls = qopt->defcls;
	sch_tree_unlock(sch);

	वापस 0;
पूर्ण

अटल व्योम
hfsc_reset_class(काष्ठा hfsc_class *cl)
अणु
	cl->cl_total        = 0;
	cl->cl_cumul        = 0;
	cl->cl_d            = 0;
	cl->cl_e            = 0;
	cl->cl_vt           = 0;
	cl->cl_vtadj        = 0;
	cl->cl_cvपंचांगin       = 0;
	cl->cl_cvtoff       = 0;
	cl->cl_vtperiod     = 0;
	cl->cl_parentperiod = 0;
	cl->cl_f            = 0;
	cl->cl_myf          = 0;
	cl->cl_cfmin        = 0;
	cl->cl_nactive      = 0;

	cl->vt_tree = RB_ROOT;
	cl->cf_tree = RB_ROOT;
	qdisc_reset(cl->qdisc);

	अगर (cl->cl_flags & HFSC_RSC)
		rtsc_init(&cl->cl_deadline, &cl->cl_rsc, 0, 0);
	अगर (cl->cl_flags & HFSC_FSC)
		rtsc_init(&cl->cl_भव, &cl->cl_fsc, 0, 0);
	अगर (cl->cl_flags & HFSC_USC)
		rtsc_init(&cl->cl_ulimit, &cl->cl_usc, 0, 0);
पूर्ण

अटल व्योम
hfsc_reset_qdisc(काष्ठा Qdisc *sch)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा hfsc_class *cl;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[i], cl_common.hnode)
			hfsc_reset_class(cl);
	पूर्ण
	q->eligible = RB_ROOT;
	qdisc_watchकरोg_cancel(&q->watchकरोg);
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
पूर्ण

अटल व्योम
hfsc_destroy_qdisc(काष्ठा Qdisc *sch)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा hlist_node *next;
	काष्ठा hfsc_class *cl;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[i], cl_common.hnode) अणु
			tcf_block_put(cl->block);
			cl->block = शून्य;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry_safe(cl, next, &q->clhash.hash[i],
					  cl_common.hnode)
			hfsc_destroy_class(sch, cl);
	पूर्ण
	qdisc_class_hash_destroy(&q->clhash);
	qdisc_watchकरोg_cancel(&q->watchकरोg);
पूर्ण

अटल पूर्णांक
hfsc_dump_qdisc(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_hfsc_qopt qopt;

	qopt.defcls = q->defcls;
	अगर (nla_put(skb, TCA_OPTIONS, माप(qopt), &qopt))
		जाओ nla_put_failure;
	वापस skb->len;

 nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक
hfsc_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch, काष्ठा sk_buff **to_मुक्त)
अणु
	अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);
	काष्ठा hfsc_class *cl;
	पूर्णांक err;
	bool first;

	cl = hfsc_classअगरy(skb, sch, &err);
	अगर (cl == शून्य) अणु
		अगर (err & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस err;
	पूर्ण

	first = !cl->qdisc->q.qlen;
	err = qdisc_enqueue(skb, cl->qdisc, to_मुक्त);
	अगर (unlikely(err != NET_XMIT_SUCCESS)) अणु
		अगर (net_xmit_drop_count(err)) अणु
			cl->qstats.drops++;
			qdisc_qstats_drop(sch);
		पूर्ण
		वापस err;
	पूर्ण

	अगर (first) अणु
		अगर (cl->cl_flags & HFSC_RSC)
			init_ed(cl, len);
		अगर (cl->cl_flags & HFSC_FSC)
			init_vf(cl, len);
		/*
		 * If this is the first packet, isolate the head so an eventual
		 * head drop beक्रमe the first dequeue operation has no chance
		 * to invalidate the deadline.
		 */
		अगर (cl->cl_flags & HFSC_RSC)
			cl->qdisc->ops->peek(cl->qdisc);

	पूर्ण

	sch->qstats.backlog += len;
	sch->q.qlen++;

	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल काष्ठा sk_buff *
hfsc_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा hfsc_sched *q = qdisc_priv(sch);
	काष्ठा hfsc_class *cl;
	काष्ठा sk_buff *skb;
	u64 cur_समय;
	अचिन्हित पूर्णांक next_len;
	पूर्णांक realसमय = 0;

	अगर (sch->q.qlen == 0)
		वापस शून्य;

	cur_समय = psched_get_समय();

	/*
	 * अगर there are eligible classes, use real-समय criteria.
	 * find the class with the minimum deadline among
	 * the eligible classes.
	 */
	cl = eltree_get_mindl(q, cur_समय);
	अगर (cl) अणु
		realसमय = 1;
	पूर्ण अन्यथा अणु
		/*
		 * use link-sharing criteria
		 * get the class with the minimum vt in the hierarchy
		 */
		cl = vttree_get_minvt(&q->root, cur_समय);
		अगर (cl == शून्य) अणु
			qdisc_qstats_overlimit(sch);
			hfsc_schedule_watchकरोg(sch);
			वापस शून्य;
		पूर्ण
	पूर्ण

	skb = qdisc_dequeue_peeked(cl->qdisc);
	अगर (skb == शून्य) अणु
		qdisc_warn_nonwc("HFSC", cl->qdisc);
		वापस शून्य;
	पूर्ण

	bstats_update(&cl->bstats, skb);
	update_vf(cl, qdisc_pkt_len(skb), cur_समय);
	अगर (realसमय)
		cl->cl_cumul += qdisc_pkt_len(skb);

	अगर (cl->cl_flags & HFSC_RSC) अणु
		अगर (cl->qdisc->q.qlen != 0) अणु
			/* update ed */
			next_len = qdisc_peek_len(cl->qdisc);
			अगर (realसमय)
				update_ed(cl, next_len);
			अन्यथा
				update_d(cl, next_len);
		पूर्ण अन्यथा अणु
			/* the class becomes passive */
			eltree_हटाओ(cl);
		पूर्ण
	पूर्ण

	qdisc_bstats_update(sch, skb);
	qdisc_qstats_backlog_dec(sch, skb);
	sch->q.qlen--;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops hfsc_class_ops = अणु
	.change		= hfsc_change_class,
	.delete		= hfsc_delete_class,
	.graft		= hfsc_graft_class,
	.leaf		= hfsc_class_leaf,
	.qlen_notअगरy	= hfsc_qlen_notअगरy,
	.find		= hfsc_search_class,
	.bind_tcf	= hfsc_bind_tcf,
	.unbind_tcf	= hfsc_unbind_tcf,
	.tcf_block	= hfsc_tcf_block,
	.dump		= hfsc_dump_class,
	.dump_stats	= hfsc_dump_class_stats,
	.walk		= hfsc_walk
पूर्ण;

अटल काष्ठा Qdisc_ops hfsc_qdisc_ops __पढ़ो_mostly = अणु
	.id		= "hfsc",
	.init		= hfsc_init_qdisc,
	.change		= hfsc_change_qdisc,
	.reset		= hfsc_reset_qdisc,
	.destroy	= hfsc_destroy_qdisc,
	.dump		= hfsc_dump_qdisc,
	.enqueue	= hfsc_enqueue,
	.dequeue	= hfsc_dequeue,
	.peek		= qdisc_peek_dequeued,
	.cl_ops		= &hfsc_class_ops,
	.priv_size	= माप(काष्ठा hfsc_sched),
	.owner		= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init
hfsc_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&hfsc_qdisc_ops);
पूर्ण

अटल व्योम __निकास
hfsc_cleanup(व्योम)
अणु
	unरेजिस्टर_qdisc(&hfsc_qdisc_ops);
पूर्ण

MODULE_LICENSE("GPL");
module_init(hfsc_init);
module_निकास(hfsc_cleanup);
