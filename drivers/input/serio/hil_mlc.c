<शैली गुरु>
/*
 * HIL MLC state machine and serio पूर्णांकerface driver
 *
 * Copyright (c) 2001 Brian S. Julin
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *
 * References:
 * HP-HIL Technical Reference Manual.  Hewlett Packard Product No. 45918A
 *
 *
 *	Driver theory of operation:
 *
 *	Some access methods and an ISR is defined by the sub-driver
 *	(e.g. hp_sdc_mlc.c).  These methods are expected to provide a
 *	few bits of logic in addition to raw access to the HIL MLC,
 *	specअगरically, the ISR, which is entirely रेजिस्टरed by the
 *	sub-driver and invoked directly, must check क्रम record
 *	termination or packet match, at which poपूर्णांक a semaphore must
 *	be cleared and then the hil_mlcs_tasklet must be scheduled.
 *
 *	The hil_mlcs_tasklet processes the state machine क्रम all MLCs
 *	each समय it runs, checking each MLC's progress at the current
 *	node in the state machine, and moving the MLC to subsequent nodes
 *	in the state machine when appropriate.  It will reschedule
 *	itself अगर output is pending.  (This rescheduling should be replaced
 *	at some poपूर्णांक with a sub-driver-specअगरic mechanism.)
 *
 *	A समयr task prods the tasklet once per second to prevent
 *	hangups when attached devices करो not वापस expected data
 *	and to initiate probes of the loop क्रम new devices.
 */

#समावेश <linux/hil_mlc.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>

MODULE_AUTHOR("Brian S. Julin <bri@calyx.com>");
MODULE_DESCRIPTION("HIL MLC serio");
MODULE_LICENSE("Dual BSD/GPL");

EXPORT_SYMBOL(hil_mlc_रेजिस्टर);
EXPORT_SYMBOL(hil_mlc_unरेजिस्टर);

#घोषणा PREFIX "HIL MLC: "

अटल LIST_HEAD(hil_mlcs);
अटल DEFINE_RWLOCK(hil_mlcs_lock);
अटल काष्ठा समयr_list	hil_mlcs_kicker;
अटल पूर्णांक			hil_mlcs_probe, hil_mlc_stop;

अटल व्योम hil_mlcs_process(अचिन्हित दीर्घ unused);
अटल DECLARE_TASKLET_DISABLED_OLD(hil_mlcs_tasklet, hil_mlcs_process);


/* #घोषणा HIL_MLC_DEBUG */

/********************** Device info/instance management **********************/

अटल व्योम hil_mlc_clear_di_map(hil_mlc *mlc, पूर्णांक val)
अणु
	पूर्णांक j;

	क्रम (j = val; j < 7 ; j++)
		mlc->di_map[j] = -1;
पूर्ण

अटल व्योम hil_mlc_clear_di_scratch(hil_mlc *mlc)
अणु
	स_रखो(&mlc->di_scratch, 0, माप(mlc->di_scratch));
पूर्ण

अटल व्योम hil_mlc_copy_di_scratch(hil_mlc *mlc, पूर्णांक idx)
अणु
	स_नकल(&mlc->di[idx], &mlc->di_scratch, माप(mlc->di_scratch));
पूर्ण

अटल पूर्णांक hil_mlc_match_di_scratch(hil_mlc *mlc)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < HIL_MLC_DEVMEM; idx++) अणु
		पूर्णांक j, found = 0;

		/* In-use slots are not eligible. */
		क्रम (j = 0; j < 7 ; j++)
			अगर (mlc->di_map[j] == idx)
				found++;

		अगर (found)
			जारी;

		अगर (!स_भेद(mlc->di + idx, &mlc->di_scratch,
				माप(mlc->di_scratch)))
			अवरोध;
	पूर्ण
	वापस idx >= HIL_MLC_DEVMEM ? -1 : idx;
पूर्ण

अटल पूर्णांक hil_mlc_find_मुक्त_di(hil_mlc *mlc)
अणु
	पूर्णांक idx;

	/* TODO: Pick all-zero slots first, failing that,
	 * अक्रमomize the slot picked among those eligible.
	 */
	क्रम (idx = 0; idx < HIL_MLC_DEVMEM; idx++) अणु
		पूर्णांक j, found = 0;

		क्रम (j = 0; j < 7 ; j++)
			अगर (mlc->di_map[j] == idx)
				found++;

		अगर (!found)
			अवरोध;
	पूर्ण

	वापस idx; /* Note: It is guaranteed at least one above will match */
पूर्ण

अटल अंतरभूत व्योम hil_mlc_clean_serio_map(hil_mlc *mlc)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < HIL_MLC_DEVMEM; idx++) अणु
		पूर्णांक j, found = 0;

		क्रम (j = 0; j < 7 ; j++)
			अगर (mlc->di_map[j] == idx)
				found++;

		अगर (!found)
			mlc->serio_map[idx].di_revmap = -1;
	पूर्ण
पूर्ण

अटल व्योम hil_mlc_send_polls(hil_mlc *mlc)
अणु
	पूर्णांक did, i, cnt;
	काष्ठा serio *serio;
	काष्ठा serio_driver *drv;

	i = cnt = 0;
	did = (mlc->ipacket[0] & HIL_PKT_ADDR_MASK) >> 8;
	serio = did ? mlc->serio[mlc->di_map[did - 1]] : शून्य;
	drv = (serio != शून्य) ? serio->drv : शून्य;

	जबतक (mlc->icount < 15 - i) अणु
		hil_packet p;

		p = mlc->ipacket[i];
		अगर (did != (p & HIL_PKT_ADDR_MASK) >> 8) अणु
			अगर (drv && drv->पूर्णांकerrupt) अणु
				drv->पूर्णांकerrupt(serio, 0, 0);
				drv->पूर्णांकerrupt(serio, HIL_ERR_INT >> 16, 0);
				drv->पूर्णांकerrupt(serio, HIL_PKT_CMD >> 8,  0);
				drv->पूर्णांकerrupt(serio, HIL_CMD_POL + cnt, 0);
			पूर्ण

			did = (p & HIL_PKT_ADDR_MASK) >> 8;
			serio = did ? mlc->serio[mlc->di_map[did-1]] : शून्य;
			drv = (serio != शून्य) ? serio->drv : शून्य;
			cnt = 0;
		पूर्ण

		cnt++;
		i++;

		अगर (drv && drv->पूर्णांकerrupt) अणु
			drv->पूर्णांकerrupt(serio, (p >> 24), 0);
			drv->पूर्णांकerrupt(serio, (p >> 16) & 0xff, 0);
			drv->पूर्णांकerrupt(serio, (p >> 8) & ~HIL_PKT_ADDR_MASK, 0);
			drv->पूर्णांकerrupt(serio, p & 0xff, 0);
		पूर्ण
	पूर्ण
पूर्ण

/*************************** State engine *********************************/

#घोषणा HILSEN_SCHED	0x000100	/* Schedule the tasklet		*/
#घोषणा HILSEN_BREAK	0x000200	/* Wait until next pass		*/
#घोषणा HILSEN_UP	0x000400	/* relative node#, decrement	*/
#घोषणा HILSEN_DOWN	0x000800	/* relative node#, increment	*/
#घोषणा HILSEN_FOLLOW	0x001000	/* use retval as next node#	*/

#घोषणा HILSEN_MASK	0x0000ff
#घोषणा HILSEN_START	0
#घोषणा HILSEN_RESTART	1
#घोषणा HILSEN_DHR	9
#घोषणा HILSEN_DHR2	10
#घोषणा HILSEN_IFC	14
#घोषणा HILSEN_HEAL0	16
#घोषणा HILSEN_HEAL	18
#घोषणा HILSEN_ACF      21
#घोषणा HILSEN_ACF2	22
#घोषणा HILSEN_DISC0	25
#घोषणा HILSEN_DISC	27
#घोषणा HILSEN_MATCH	40
#घोषणा HILSEN_OPERATE	41
#घोषणा HILSEN_PROBE	44
#घोषणा HILSEN_DSR	52
#घोषणा HILSEN_REPOLL	55
#घोषणा HILSEN_IFCACF	58
#घोषणा HILSEN_END	60

#घोषणा HILSEN_NEXT	(HILSEN_DOWN | 1)
#घोषणा HILSEN_SAME	(HILSEN_DOWN | 0)
#घोषणा HILSEN_LAST	(HILSEN_UP | 1)

#घोषणा HILSEN_DOZE	(HILSEN_SAME | HILSEN_SCHED | HILSEN_BREAK)
#घोषणा HILSEN_SLEEP	(HILSEN_SAME | HILSEN_BREAK)

अटल पूर्णांक hilse_match(hil_mlc *mlc, पूर्णांक unused)
अणु
	पूर्णांक rc;

	rc = hil_mlc_match_di_scratch(mlc);
	अगर (rc == -1) अणु
		rc = hil_mlc_find_मुक्त_di(mlc);
		अगर (rc == -1)
			जाओ err;

#अगर_घोषित HIL_MLC_DEBUG
		prपूर्णांकk(KERN_DEBUG PREFIX "new in slot %i\n", rc);
#पूर्ण_अगर
		hil_mlc_copy_di_scratch(mlc, rc);
		mlc->di_map[mlc->ddi] = rc;
		mlc->serio_map[rc].di_revmap = mlc->ddi;
		hil_mlc_clean_serio_map(mlc);
		serio_rescan(mlc->serio[rc]);
		वापस -1;
	पूर्ण

	mlc->di_map[mlc->ddi] = rc;
#अगर_घोषित HIL_MLC_DEBUG
	prपूर्णांकk(KERN_DEBUG PREFIX "same in slot %i\n", rc);
#पूर्ण_अगर
	mlc->serio_map[rc].di_revmap = mlc->ddi;
	hil_mlc_clean_serio_map(mlc);
	वापस 0;

 err:
	prपूर्णांकk(KERN_ERR PREFIX "Residual device slots exhausted, close some serios!\n");
	वापस 1;
पूर्ण

/* An LCV used to prevent runaway loops, क्रमces 5 second sleep when reset. */
अटल पूर्णांक hilse_init_lcv(hil_mlc *mlc, पूर्णांक unused)
अणु
	समय64_t now = kसमय_get_seconds();

	अगर (mlc->lcv && (now - mlc->lcv_समय) < 5)
		वापस -1;

	mlc->lcv_समय = now;
	mlc->lcv = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक hilse_inc_lcv(hil_mlc *mlc, पूर्णांक lim)
अणु
	वापस mlc->lcv++ >= lim ? -1 : 0;
पूर्ण

#अगर 0
अटल पूर्णांक hilse_set_lcv(hil_mlc *mlc, पूर्णांक val)
अणु
	mlc->lcv = val;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Management of the discovered device index (zero based, -1 means no devs) */
अटल पूर्णांक hilse_set_ddi(hil_mlc *mlc, पूर्णांक val)
अणु
	mlc->ddi = val;
	hil_mlc_clear_di_map(mlc, val + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक hilse_dec_ddi(hil_mlc *mlc, पूर्णांक unused)
अणु
	mlc->ddi--;
	अगर (mlc->ddi <= -1) अणु
		mlc->ddi = -1;
		hil_mlc_clear_di_map(mlc, 0);
		वापस -1;
	पूर्ण
	hil_mlc_clear_di_map(mlc, mlc->ddi + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक hilse_inc_ddi(hil_mlc *mlc, पूर्णांक unused)
अणु
	BUG_ON(mlc->ddi >= 6);
	mlc->ddi++;

	वापस 0;
पूर्ण

अटल पूर्णांक hilse_take_idd(hil_mlc *mlc, पूर्णांक unused)
अणु
	पूर्णांक i;

	/* Help the state engine:
	 * Is this a real IDD response or just an echo?
	 *
	 * Real IDD response करोes not start with a command.
	 */
	अगर (mlc->ipacket[0] & HIL_PKT_CMD)
		जाओ bail;

	/* Should have the command echoed further करोwn. */
	क्रम (i = 1; i < 16; i++) अणु
		अगर (((mlc->ipacket[i] & HIL_PKT_ADDR_MASK) ==
		     (mlc->ipacket[0] & HIL_PKT_ADDR_MASK)) &&
		    (mlc->ipacket[i] & HIL_PKT_CMD) &&
		    ((mlc->ipacket[i] & HIL_PKT_DATA_MASK) == HIL_CMD_IDD))
			अवरोध;
	पूर्ण
	अगर (i > 15)
		जाओ bail;

	/* And the rest of the packets should still be clear. */
	जबतक (++i < 16)
		अगर (mlc->ipacket[i])
			अवरोध;

	अगर (i < 16)
		जाओ bail;

	क्रम (i = 0; i < 16; i++)
		mlc->di_scratch.idd[i] =
			mlc->ipacket[i] & HIL_PKT_DATA_MASK;

	/* Next step is to see अगर RSC supported */
	अगर (mlc->di_scratch.idd[1] & HIL_IDD_HEADER_RSC)
		वापस HILSEN_NEXT;

	अगर (mlc->di_scratch.idd[1] & HIL_IDD_HEADER_EXD)
		वापस HILSEN_DOWN | 4;

	वापस 0;

 bail:
	mlc->ddi--;

	वापस -1; /* This should send us off to ACF */
पूर्ण

अटल पूर्णांक hilse_take_rsc(hil_mlc *mlc, पूर्णांक unused)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		mlc->di_scratch.rsc[i] =
			mlc->ipacket[i] & HIL_PKT_DATA_MASK;

	/* Next step is to see अगर EXD supported (IDD has alपढ़ोy been पढ़ो) */
	अगर (mlc->di_scratch.idd[1] & HIL_IDD_HEADER_EXD)
		वापस HILSEN_NEXT;

	वापस 0;
पूर्ण

अटल पूर्णांक hilse_take_exd(hil_mlc *mlc, पूर्णांक unused)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		mlc->di_scratch.exd[i] =
			mlc->ipacket[i] & HIL_PKT_DATA_MASK;

	/* Next step is to see अगर RNM supported. */
	अगर (mlc->di_scratch.exd[0] & HIL_EXD_HEADER_RNM)
		वापस HILSEN_NEXT;

	वापस 0;
पूर्ण

अटल पूर्णांक hilse_take_rnm(hil_mlc *mlc, पूर्णांक unused)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		mlc->di_scratch.rnm[i] =
			mlc->ipacket[i] & HIL_PKT_DATA_MASK;

	prपूर्णांकk(KERN_INFO PREFIX "Device name gotten: %16s\n",
			mlc->di_scratch.rnm);

	वापस 0;
पूर्ण

अटल पूर्णांक hilse_operate(hil_mlc *mlc, पूर्णांक repoll)
अणु

	अगर (mlc->opercnt == 0)
		hil_mlcs_probe = 0;
	mlc->opercnt = 1;

	hil_mlc_send_polls(mlc);

	अगर (!hil_mlcs_probe)
		वापस 0;
	hil_mlcs_probe = 0;
	mlc->opercnt = 0;
	वापस 1;
पूर्ण

#घोषणा FUNC(funct, funct_arg, zero_rc, neg_rc, pos_rc) \
अणु HILSE_FUNC,		अणु .func = funct पूर्ण, funct_arg, zero_rc, neg_rc, pos_rc पूर्ण,
#घोषणा OUT(pack) \
अणु HILSE_OUT,		अणु .packet = pack पूर्ण, 0, HILSEN_NEXT, HILSEN_DOZE, 0 पूर्ण,
#घोषणा CTS \
अणु HILSE_CTS,		अणु .packet = 0    पूर्ण, 0, HILSEN_NEXT | HILSEN_SCHED | HILSEN_BREAK, HILSEN_DOZE, 0 पूर्ण,
#घोषणा EXPECT(comp, to, got, got_wrong, समयd_out) \
अणु HILSE_EXPECT,		अणु .packet = comp पूर्ण, to, got, got_wrong, समयd_out पूर्ण,
#घोषणा EXPECT_LAST(comp, to, got, got_wrong, समयd_out) \
अणु HILSE_EXPECT_LAST,	अणु .packet = comp पूर्ण, to, got, got_wrong, समयd_out पूर्ण,
#घोषणा EXPECT_DISC(comp, to, got, got_wrong, समयd_out) \
अणु HILSE_EXPECT_DISC,	अणु .packet = comp पूर्ण, to, got, got_wrong, समयd_out पूर्ण,
#घोषणा IN(to, got, got_error, समयd_out) \
अणु HILSE_IN,		अणु .packet = 0    पूर्ण, to, got, got_error, समयd_out पूर्ण,
#घोषणा OUT_DISC(pack) \
अणु HILSE_OUT_DISC,	अणु .packet = pack पूर्ण, 0, 0, 0, 0 पूर्ण,
#घोषणा OUT_LAST(pack) \
अणु HILSE_OUT_LAST,	अणु .packet = pack पूर्ण, 0, 0, 0, 0 पूर्ण,

अटल स्थिर काष्ठा hilse_node hil_mlc_se[HILSEN_END] = अणु

	/* 0  HILSEN_START */
	FUNC(hilse_init_lcv, 0,	HILSEN_NEXT,	HILSEN_SLEEP,	0)

	/* 1  HILSEN_RESTART */
	FUNC(hilse_inc_lcv, 10,	HILSEN_NEXT,	HILSEN_START,  0)
	OUT(HIL_CTRL_ONLY)			/* Disable APE */
	CTS

#घोषणा TEST_PACKET(x) \
(HIL_PKT_CMD | (x << HIL_PKT_ADDR_SHIFT) | x << 4 | x)

	OUT(HIL_DO_ALTER_CTRL | HIL_CTRL_TEST | TEST_PACKET(0x5))
	EXPECT(HIL_ERR_INT | TEST_PACKET(0x5),
	       2000,		HILSEN_NEXT,	HILSEN_RESTART,	HILSEN_RESTART)
	OUT(HIL_DO_ALTER_CTRL | HIL_CTRL_TEST | TEST_PACKET(0xa))
	EXPECT(HIL_ERR_INT | TEST_PACKET(0xa),
	       2000,		HILSEN_NEXT,	HILSEN_RESTART,	HILSEN_RESTART)
	OUT(HIL_CTRL_ONLY | 0)			/* Disable test mode */

	/* 9  HILSEN_DHR */
	FUNC(hilse_init_lcv, 0,	HILSEN_NEXT,	HILSEN_SLEEP,	0)

	/* 10 HILSEN_DHR2 */
	FUNC(hilse_inc_lcv, 10,	HILSEN_NEXT,	HILSEN_START,	0)
	FUNC(hilse_set_ddi, -1,	HILSEN_NEXT,	0,		0)
	OUT(HIL_PKT_CMD | HIL_CMD_DHR)
	IN(300000,		HILSEN_DHR2,	HILSEN_DHR2,	HILSEN_NEXT)

	/* 14 HILSEN_IFC */
	OUT(HIL_PKT_CMD | HIL_CMD_IFC)
	EXPECT(HIL_PKT_CMD | HIL_CMD_IFC | HIL_ERR_INT,
	       20000,		HILSEN_DISC,	HILSEN_DHR2,	HILSEN_NEXT )

	/* If devices are there, they weren't in PUP or other loopback mode.
	 * We're more concerned at this poपूर्णांक with restoring operation
	 * to devices than discovering new ones, so we try to salvage
	 * the loop configuration by closing off the loop.
	 */

	/* 16 HILSEN_HEAL0 */
	FUNC(hilse_dec_ddi, 0,	HILSEN_NEXT,	HILSEN_ACF,	0)
	FUNC(hilse_inc_ddi, 0,	HILSEN_NEXT,	0,		0)

	/* 18 HILSEN_HEAL */
	OUT_LAST(HIL_CMD_ELB)
	EXPECT_LAST(HIL_CMD_ELB | HIL_ERR_INT,
		    20000,	HILSEN_REPOLL,	HILSEN_DSR,	HILSEN_NEXT)
	FUNC(hilse_dec_ddi, 0,	HILSEN_HEAL,	HILSEN_NEXT,	0)

	/* 21 HILSEN_ACF */
	FUNC(hilse_init_lcv, 0,	HILSEN_NEXT,	HILSEN_DOZE,	0)

	/* 22 HILSEN_ACF2 */
	FUNC(hilse_inc_lcv, 10,	HILSEN_NEXT,	HILSEN_START,	0)
	OUT(HIL_PKT_CMD | HIL_CMD_ACF | 1)
	IN(20000,		HILSEN_NEXT,	HILSEN_DSR,	HILSEN_NEXT)

	/* 25 HILSEN_DISC0 */
	OUT_DISC(HIL_PKT_CMD | HIL_CMD_ELB)
	EXPECT_DISC(HIL_PKT_CMD | HIL_CMD_ELB | HIL_ERR_INT,
	       20000,		HILSEN_NEXT,	HILSEN_DSR,	HILSEN_DSR)

	/* Only enter here अगर response just received */
	/* 27 HILSEN_DISC */
	OUT_DISC(HIL_PKT_CMD | HIL_CMD_IDD)
	EXPECT_DISC(HIL_PKT_CMD | HIL_CMD_IDD | HIL_ERR_INT,
	       20000,		HILSEN_NEXT,	HILSEN_DSR,	HILSEN_START)
	FUNC(hilse_inc_ddi,  0,	HILSEN_NEXT,	HILSEN_START,	0)
	FUNC(hilse_take_idd, 0,	HILSEN_MATCH,	HILSEN_IFCACF,	HILSEN_FOLLOW)
	OUT_LAST(HIL_PKT_CMD | HIL_CMD_RSC)
	EXPECT_LAST(HIL_PKT_CMD | HIL_CMD_RSC | HIL_ERR_INT,
	       30000,		HILSEN_NEXT,	HILSEN_DSR,	HILSEN_DSR)
	FUNC(hilse_take_rsc, 0,	HILSEN_MATCH,	0,		HILSEN_FOLLOW)
	OUT_LAST(HIL_PKT_CMD | HIL_CMD_EXD)
	EXPECT_LAST(HIL_PKT_CMD | HIL_CMD_EXD | HIL_ERR_INT,
	       30000,		HILSEN_NEXT,	HILSEN_DSR,	HILSEN_DSR)
	FUNC(hilse_take_exd, 0,	HILSEN_MATCH,	0,		HILSEN_FOLLOW)
	OUT_LAST(HIL_PKT_CMD | HIL_CMD_RNM)
	EXPECT_LAST(HIL_PKT_CMD | HIL_CMD_RNM | HIL_ERR_INT,
	       30000,		HILSEN_NEXT,	HILSEN_DSR,	HILSEN_DSR)
	FUNC(hilse_take_rnm, 0, HILSEN_MATCH,	0,		0)

	/* 40 HILSEN_MATCH */
	FUNC(hilse_match, 0,	HILSEN_NEXT,	HILSEN_NEXT,	/* TODO */ 0)

	/* 41 HILSEN_OPERATE */
	OUT(HIL_PKT_CMD | HIL_CMD_POL)
	EXPECT(HIL_PKT_CMD | HIL_CMD_POL | HIL_ERR_INT,
	       20000,		HILSEN_NEXT,	HILSEN_DSR,	HILSEN_NEXT)
	FUNC(hilse_operate, 0,	HILSEN_OPERATE,	HILSEN_IFC,	HILSEN_NEXT)

	/* 44 HILSEN_PROBE */
	OUT_LAST(HIL_PKT_CMD | HIL_CMD_EPT)
	IN(10000,		HILSEN_DISC,	HILSEN_DSR,	HILSEN_NEXT)
	OUT_DISC(HIL_PKT_CMD | HIL_CMD_ELB)
	IN(10000,		HILSEN_DISC,	HILSEN_DSR,	HILSEN_NEXT)
	OUT(HIL_PKT_CMD | HIL_CMD_ACF | 1)
	IN(10000,		HILSEN_DISC0,	HILSEN_DSR,	HILSEN_NEXT)
	OUT_LAST(HIL_PKT_CMD | HIL_CMD_ELB)
	IN(10000,		HILSEN_OPERATE,	HILSEN_DSR,	HILSEN_DSR)

	/* 52 HILSEN_DSR */
	FUNC(hilse_set_ddi, -1,	HILSEN_NEXT,	0,		0)
	OUT(HIL_PKT_CMD | HIL_CMD_DSR)
	IN(20000,		HILSEN_DHR,	HILSEN_DHR,	HILSEN_IFC)

	/* 55 HILSEN_REPOLL */
	OUT(HIL_PKT_CMD | HIL_CMD_RPL)
	EXPECT(HIL_PKT_CMD | HIL_CMD_RPL | HIL_ERR_INT,
	       20000,		HILSEN_NEXT,	HILSEN_DSR,	HILSEN_NEXT)
	FUNC(hilse_operate, 1,	HILSEN_OPERATE,	HILSEN_IFC,	HILSEN_PROBE)

	/* 58 HILSEN_IFCACF */
	OUT(HIL_PKT_CMD | HIL_CMD_IFC)
	EXPECT(HIL_PKT_CMD | HIL_CMD_IFC | HIL_ERR_INT,
	       20000,		HILSEN_ACF2,	HILSEN_DHR2,	HILSEN_HEAL)

	/* 60 HILSEN_END */
पूर्ण;

अटल अंतरभूत व्योम hilse_setup_input(hil_mlc *mlc, स्थिर काष्ठा hilse_node *node)
अणु

	चयन (node->act) अणु
	हाल HILSE_EXPECT_DISC:
		mlc->imatch = node->object.packet;
		mlc->imatch |= ((mlc->ddi + 2) << HIL_PKT_ADDR_SHIFT);
		अवरोध;
	हाल HILSE_EXPECT_LAST:
		mlc->imatch = node->object.packet;
		mlc->imatch |= ((mlc->ddi + 1) << HIL_PKT_ADDR_SHIFT);
		अवरोध;
	हाल HILSE_EXPECT:
		mlc->imatch = node->object.packet;
		अवरोध;
	हाल HILSE_IN:
		mlc->imatch = 0;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	mlc->istarted = 1;
	mlc->पूर्णांकimeout = usecs_to_jअगरfies(node->arg);
	mlc->instart = jअगरfies;
	mlc->icount = 15;
	स_रखो(mlc->ipacket, 0, 16 * माप(hil_packet));
	BUG_ON(करोwn_trylock(&mlc->isem));
पूर्ण

#अगर_घोषित HIL_MLC_DEBUG
अटल पूर्णांक करोze;
अटल पूर्णांक seidx; /* For debug */
#पूर्ण_अगर

अटल पूर्णांक hilse_करोnode(hil_mlc *mlc)
अणु
	स्थिर काष्ठा hilse_node *node;
	पूर्णांक nextidx = 0;
	पूर्णांक sched_दीर्घ = 0;
	अचिन्हित दीर्घ flags;

#अगर_घोषित HIL_MLC_DEBUG
	अगर (mlc->seidx && mlc->seidx != seidx &&
	    mlc->seidx != 41 && mlc->seidx != 42 && mlc->seidx != 43) अणु
		prपूर्णांकk(KERN_DEBUG PREFIX "z%i \n {%i}", करोze, mlc->seidx);
		करोze = 0;
	पूर्ण

	seidx = mlc->seidx;
#पूर्ण_अगर
	node = hil_mlc_se + mlc->seidx;

	चयन (node->act) अणु
		पूर्णांक rc;
		hil_packet pack;

	हाल HILSE_FUNC:
		BUG_ON(node->object.func == शून्य);
		rc = node->object.func(mlc, node->arg);
		nextidx = (rc > 0) ? node->ugly :
			((rc < 0) ? node->bad : node->good);
		अगर (nextidx == HILSEN_FOLLOW)
			nextidx = rc;
		अवरोध;

	हाल HILSE_EXPECT_LAST:
	हाल HILSE_EXPECT_DISC:
	हाल HILSE_EXPECT:
	हाल HILSE_IN:
		/* Alपढ़ोy set up from previous HILSE_OUT_* */
		ग_लिखो_lock_irqsave(&mlc->lock, flags);
		rc = mlc->in(mlc, node->arg);
		अगर (rc == 2)  अणु
			nextidx = HILSEN_DOZE;
			sched_दीर्घ = 1;
			ग_लिखो_unlock_irqrestore(&mlc->lock, flags);
			अवरोध;
		पूर्ण
		अगर (rc == 1)
			nextidx = node->ugly;
		अन्यथा अगर (rc == 0)
			nextidx = node->good;
		अन्यथा
			nextidx = node->bad;
		mlc->istarted = 0;
		ग_लिखो_unlock_irqrestore(&mlc->lock, flags);
		अवरोध;

	हाल HILSE_OUT_LAST:
		ग_लिखो_lock_irqsave(&mlc->lock, flags);
		pack = node->object.packet;
		pack |= ((mlc->ddi + 1) << HIL_PKT_ADDR_SHIFT);
		जाओ out;

	हाल HILSE_OUT_DISC:
		ग_लिखो_lock_irqsave(&mlc->lock, flags);
		pack = node->object.packet;
		pack |= ((mlc->ddi + 2) << HIL_PKT_ADDR_SHIFT);
		जाओ out;

	हाल HILSE_OUT:
		ग_लिखो_lock_irqsave(&mlc->lock, flags);
		pack = node->object.packet;
	out:
		अगर (!mlc->istarted) अणु
			/* Prepare to receive input */
			अगर ((node + 1)->act & HILSE_IN)
				hilse_setup_input(mlc, node + 1);
		पूर्ण

		ग_लिखो_unlock_irqrestore(&mlc->lock, flags);

		अगर (करोwn_trylock(&mlc->osem)) अणु
			nextidx = HILSEN_DOZE;
			अवरोध;
		पूर्ण
		up(&mlc->osem);

		ग_लिखो_lock_irqsave(&mlc->lock, flags);
		अगर (!mlc->ostarted) अणु
			mlc->ostarted = 1;
			mlc->opacket = pack;
			rc = mlc->out(mlc);
			nextidx = HILSEN_DOZE;
			ग_लिखो_unlock_irqrestore(&mlc->lock, flags);
			अगर (rc) अणु
				hil_mlc_stop = 1;
				वापस 1;
			पूर्ण
			अवरोध;
		पूर्ण
		mlc->ostarted = 0;
		mlc->instart = jअगरfies;
		ग_लिखो_unlock_irqrestore(&mlc->lock, flags);
		nextidx = HILSEN_NEXT;
		अवरोध;

	हाल HILSE_CTS:
		ग_लिखो_lock_irqsave(&mlc->lock, flags);
		rc = mlc->cts(mlc);
		nextidx = rc ? node->bad : node->good;
		ग_लिखो_unlock_irqrestore(&mlc->lock, flags);
		अगर (rc) अणु
			hil_mlc_stop = 1;
			वापस 1;
		पूर्ण
		अवरोध;

	शेष:
		BUG();
	पूर्ण

#अगर_घोषित HIL_MLC_DEBUG
	अगर (nextidx == HILSEN_DOZE)
		करोze++;
#पूर्ण_अगर

	जबतक (nextidx & HILSEN_SCHED) अणु
		अचिन्हित दीर्घ now = jअगरfies;

		अगर (!sched_दीर्घ)
			जाओ sched;

		अगर (समय_after(now, mlc->instart + mlc->पूर्णांकimeout))
			 जाओ sched;
		mod_समयr(&hil_mlcs_kicker, mlc->instart + mlc->पूर्णांकimeout);
		अवरोध;
	sched:
		tasklet_schedule(&hil_mlcs_tasklet);
		अवरोध;
	पूर्ण

	अगर (nextidx & HILSEN_DOWN)
		mlc->seidx += nextidx & HILSEN_MASK;
	अन्यथा अगर (nextidx & HILSEN_UP)
		mlc->seidx -= nextidx & HILSEN_MASK;
	अन्यथा
		mlc->seidx = nextidx & HILSEN_MASK;

	अगर (nextidx & HILSEN_BREAK)
		वापस 1;

	वापस 0;
पूर्ण

/******************** tasklet context functions **************************/
अटल व्योम hil_mlcs_process(अचिन्हित दीर्घ unused)
अणु
	काष्ठा list_head *पंचांगp;

	पढ़ो_lock(&hil_mlcs_lock);
	list_क्रम_each(पंचांगp, &hil_mlcs) अणु
		काष्ठा hil_mlc *mlc = list_entry(पंचांगp, hil_mlc, list);
		जबतक (hilse_करोnode(mlc) == 0) अणु
#अगर_घोषित HIL_MLC_DEBUG
			अगर (mlc->seidx != 41 &&
			    mlc->seidx != 42 &&
			    mlc->seidx != 43)
				prपूर्णांकk(KERN_DEBUG PREFIX " + ");
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&hil_mlcs_lock);
पूर्ण

/************************* Keepalive समयr task *********************/

अटल व्योम hil_mlcs_समयr(काष्ठा समयr_list *unused)
अणु
	अगर (hil_mlc_stop) अणु
		/* could not send packet - stop immediately. */
		pr_warn(PREFIX "HIL seems stuck - Disabling HIL MLC.\n");
		वापस;
	पूर्ण

	hil_mlcs_probe = 1;
	tasklet_schedule(&hil_mlcs_tasklet);
	/* Re-insert the periodic task. */
	अगर (!समयr_pending(&hil_mlcs_kicker))
		mod_समयr(&hil_mlcs_kicker, jअगरfies + HZ);
पूर्ण

/******************** user/kernel context functions **********************/

अटल पूर्णांक hil_mlc_serio_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर c)
अणु
	काष्ठा hil_mlc_serio_map *map;
	काष्ठा hil_mlc *mlc;
	काष्ठा serio_driver *drv;
	uपूर्णांक8_t *idx, *last;

	map = serio->port_data;
	BUG_ON(map == शून्य);

	mlc = map->mlc;
	BUG_ON(mlc == शून्य);

	mlc->serio_opacket[map->didx] |=
		((hil_packet)c) << (8 * (3 - mlc->serio_oidx[map->didx]));

	अगर (mlc->serio_oidx[map->didx] >= 3) अणु
		/* क्रम now only commands */
		अगर (!(mlc->serio_opacket[map->didx] & HIL_PKT_CMD))
			वापस -EIO;
		चयन (mlc->serio_opacket[map->didx] & HIL_PKT_DATA_MASK) अणु
		हाल HIL_CMD_IDD:
			idx = mlc->di[map->didx].idd;
			जाओ emu;
		हाल HIL_CMD_RSC:
			idx = mlc->di[map->didx].rsc;
			जाओ emu;
		हाल HIL_CMD_EXD:
			idx = mlc->di[map->didx].exd;
			जाओ emu;
		हाल HIL_CMD_RNM:
			idx = mlc->di[map->didx].rnm;
			जाओ emu;
		शेष:
			अवरोध;
		पूर्ण
		mlc->serio_oidx[map->didx] = 0;
		mlc->serio_opacket[map->didx] = 0;
	पूर्ण

	mlc->serio_oidx[map->didx]++;
	वापस -EIO;
 emu:
	drv = serio->drv;
	BUG_ON(drv == शून्य);

	last = idx + 15;
	जबतक ((last != idx) && (*last == 0))
		last--;

	जबतक (idx != last) अणु
		drv->पूर्णांकerrupt(serio, 0, 0);
		drv->पूर्णांकerrupt(serio, HIL_ERR_INT >> 16, 0);
		drv->पूर्णांकerrupt(serio, 0, 0);
		drv->पूर्णांकerrupt(serio, *idx, 0);
		idx++;
	पूर्ण
	drv->पूर्णांकerrupt(serio, 0, 0);
	drv->पूर्णांकerrupt(serio, HIL_ERR_INT >> 16, 0);
	drv->पूर्णांकerrupt(serio, HIL_PKT_CMD >> 8, 0);
	drv->पूर्णांकerrupt(serio, *idx, 0);

	mlc->serio_oidx[map->didx] = 0;
	mlc->serio_opacket[map->didx] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक hil_mlc_serio_खोलो(काष्ठा serio *serio)
अणु
	काष्ठा hil_mlc_serio_map *map;
	काष्ठा hil_mlc *mlc;

	अगर (serio_get_drvdata(serio) != शून्य)
		वापस -EBUSY;

	map = serio->port_data;
	BUG_ON(map == शून्य);

	mlc = map->mlc;
	BUG_ON(mlc == शून्य);

	वापस 0;
पूर्ण

अटल व्योम hil_mlc_serio_बंद(काष्ठा serio *serio)
अणु
	काष्ठा hil_mlc_serio_map *map;
	काष्ठा hil_mlc *mlc;

	map = serio->port_data;
	BUG_ON(map == शून्य);

	mlc = map->mlc;
	BUG_ON(mlc == शून्य);

	serio_set_drvdata(serio, शून्य);
	serio->drv = शून्य;
	/* TODO wake up पूर्णांकerruptable */
पूर्ण

अटल स्थिर काष्ठा serio_device_id hil_mlc_serio_id = अणु
	.type = SERIO_HIL_MLC,
	.proto = SERIO_HIL,
	.extra = SERIO_ANY,
	.id = SERIO_ANY,
पूर्ण;

पूर्णांक hil_mlc_रेजिस्टर(hil_mlc *mlc)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	BUG_ON(mlc == शून्य);

	mlc->istarted = 0;
	mlc->ostarted = 0;

	rwlock_init(&mlc->lock);
	sema_init(&mlc->osem, 1);

	sema_init(&mlc->isem, 1);
	mlc->icount = -1;
	mlc->imatch = 0;

	mlc->opercnt = 0;

	sema_init(&(mlc->csem), 0);

	hil_mlc_clear_di_scratch(mlc);
	hil_mlc_clear_di_map(mlc, 0);
	क्रम (i = 0; i < HIL_MLC_DEVMEM; i++) अणु
		काष्ठा serio *mlc_serio;
		hil_mlc_copy_di_scratch(mlc, i);
		mlc_serio = kzalloc(माप(*mlc_serio), GFP_KERNEL);
		mlc->serio[i] = mlc_serio;
		अगर (!mlc->serio[i]) अणु
			क्रम (; i >= 0; i--)
				kमुक्त(mlc->serio[i]);
			वापस -ENOMEM;
		पूर्ण
		snम_लिखो(mlc_serio->name, माप(mlc_serio->name)-1, "HIL_SERIO%d", i);
		snम_लिखो(mlc_serio->phys, माप(mlc_serio->phys)-1, "HIL%d", i);
		mlc_serio->id			= hil_mlc_serio_id;
		mlc_serio->id.id		= i; /* HIL port no. */
		mlc_serio->ग_लिखो		= hil_mlc_serio_ग_लिखो;
		mlc_serio->खोलो			= hil_mlc_serio_खोलो;
		mlc_serio->बंद		= hil_mlc_serio_बंद;
		mlc_serio->port_data		= &(mlc->serio_map[i]);
		mlc->serio_map[i].mlc		= mlc;
		mlc->serio_map[i].didx		= i;
		mlc->serio_map[i].di_revmap	= -1;
		mlc->serio_opacket[i]		= 0;
		mlc->serio_oidx[i]		= 0;
		serio_रेजिस्टर_port(mlc_serio);
	पूर्ण

	mlc->tasklet = &hil_mlcs_tasklet;

	ग_लिखो_lock_irqsave(&hil_mlcs_lock, flags);
	list_add_tail(&mlc->list, &hil_mlcs);
	mlc->seidx = HILSEN_START;
	ग_लिखो_unlock_irqrestore(&hil_mlcs_lock, flags);

	tasklet_schedule(&hil_mlcs_tasklet);
	वापस 0;
पूर्ण

पूर्णांक hil_mlc_unरेजिस्टर(hil_mlc *mlc)
अणु
	काष्ठा list_head *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	BUG_ON(mlc == शून्य);

	ग_लिखो_lock_irqsave(&hil_mlcs_lock, flags);
	list_क्रम_each(पंचांगp, &hil_mlcs)
		अगर (list_entry(पंचांगp, hil_mlc, list) == mlc)
			जाओ found;

	/* not found in list */
	ग_लिखो_unlock_irqrestore(&hil_mlcs_lock, flags);
	tasklet_schedule(&hil_mlcs_tasklet);
	वापस -ENODEV;

 found:
	list_del(पंचांगp);
	ग_लिखो_unlock_irqrestore(&hil_mlcs_lock, flags);

	क्रम (i = 0; i < HIL_MLC_DEVMEM; i++) अणु
		serio_unरेजिस्टर_port(mlc->serio[i]);
		mlc->serio[i] = शून्य;
	पूर्ण

	tasklet_schedule(&hil_mlcs_tasklet);
	वापस 0;
पूर्ण

/**************************** Module पूर्णांकerface *************************/

अटल पूर्णांक __init hil_mlc_init(व्योम)
अणु
	समयr_setup(&hil_mlcs_kicker, &hil_mlcs_समयr, 0);
	mod_समयr(&hil_mlcs_kicker, jअगरfies + HZ);

	tasklet_enable(&hil_mlcs_tasklet);

	वापस 0;
पूर्ण

अटल व्योम __निकास hil_mlc_निकास(व्योम)
अणु
	del_समयr_sync(&hil_mlcs_kicker);
	tasklet_समाप्त(&hil_mlcs_tasklet);
पूर्ण

module_init(hil_mlc_init);
module_निकास(hil_mlc_निकास);
