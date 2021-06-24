<शैली गुरु>
/*
 * HP Human Interface Loop Master Link Controller driver.
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
 */

#समावेश <linux/hil.h>
#समावेश <linux/समय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/serपन.स>
#समावेश <linux/list.h>

प्रकार काष्ठा hil_mlc hil_mlc;

/* The HIL has a complicated state engine.
 * We define the काष्ठाure of nodes in the state engine here.
 */
क्रमागत hilse_act अणु
  	/* HILSE_OUT prepares to receive input अगर the next node
	 * is an IN or EXPECT, and then sends the given packet.
	 */
	HILSE_OUT = 0,

  	/* HILSE_CTS checks अगर the loop is busy. */
	HILSE_CTS,

	/* HILSE_OUT_LAST sends the given command packet to 
	 * the last configured/running device on the loop.
	 */
	HILSE_OUT_LAST,

	/* HILSE_OUT_DISC sends the given command packet to
	 * the next device past the last configured/running one.
	 */
	HILSE_OUT_DISC,

	/* HILSE_FUNC runs a callback function with given arguments.
	 * a positive वापस value causes the "ugly" branch to be taken.
	 */
	HILSE_FUNC,

  	/* HILSE_IN simply expects any non-errored packet to arrive 
	 * within arg usecs.
	 */
	HILSE_IN		= 0x100,

  	/* HILSE_EXPECT expects a particular packet to arrive 
	 * within arg usecs, any other packet is considered an error.
	 */
	HILSE_EXPECT,

  	/* HILSE_EXPECT_LAST as above but dev field should be last 
	 * discovered/operational device.
	 */
	HILSE_EXPECT_LAST,

  	/* HILSE_EXPECT_LAST as above but dev field should be first 
	 * undiscovered/inoperational device.
	 */
	HILSE_EXPECT_DISC
पूर्ण;

प्रकार पूर्णांक	(hilse_func) (hil_mlc *mlc, पूर्णांक arg);
काष्ठा hilse_node अणु
	क्रमागत hilse_act		act;	/* How to process this node         */
	जोड़ अणु
		hilse_func	*func;	/* Function to call अगर HILSE_FUNC   */
		hil_packet	packet;	/* Packet to send or to compare     */
	पूर्ण object;
	पूर्णांक			arg;	/* Timeout in usec or parm क्रम func */
	पूर्णांक			good;	/* Node to jump to on success       */
	पूर्णांक			bad;	/* Node to jump to on error         */
	पूर्णांक			ugly;	/* Node to jump to on समयout       */
पूर्ण;

/* Methods क्रम back-end drivers, e.g. hp_sdc_mlc */
प्रकार पूर्णांक	(hil_mlc_cts) (hil_mlc *mlc);
प्रकार पूर्णांक	(hil_mlc_out) (hil_mlc *mlc);
प्रकार पूर्णांक	(hil_mlc_in)  (hil_mlc *mlc, suseconds_t समयout);

काष्ठा hil_mlc_devinfo अणु
	uपूर्णांक8_t	idd[16];	/* Device ID Byte and Describe Record */
	uपूर्णांक8_t	rsc[16];	/* Security Code Header and Record */
	uपूर्णांक8_t	exd[16];	/* Extended Describe Record */
	uपूर्णांक8_t	rnm[16];	/* Device name as वापसed by RNM command */
पूर्ण;

काष्ठा hil_mlc_serio_map अणु
	hil_mlc *mlc;
	पूर्णांक di_revmap;
	पूर्णांक didx;
पूर्ण;

/* How many (possibly old/detached) devices the we try to keep track of */
#घोषणा HIL_MLC_DEVMEM 16

काष्ठा hil_mlc अणु
	काष्ठा list_head	list;	/* hil_mlc is organized as linked list */

	rwlock_t		lock;

	व्योम *priv; /* Data specअगरic to a particular type of MLC */

	पूर्णांक 			seidx;	/* Current node in state engine */
	पूर्णांक			istarted, ostarted;

	hil_mlc_cts		*cts;
	काष्ठा semaphore	csem;   /* Raised when loop idle */

	hil_mlc_out		*out;
	काष्ठा semaphore	osem;   /* Raised when outpacket dispatched */
	hil_packet		opacket;

	hil_mlc_in		*in;
	काष्ठा semaphore	isem;   /* Raised when a packet arrives */
	hil_packet		ipacket[16];
	hil_packet		imatch;
	पूर्णांक			icount;
	अचिन्हित दीर्घ		instart;
	अचिन्हित दीर्घ		पूर्णांकimeout;

	पूर्णांक			ddi;	/* Last operational device id */
	पूर्णांक			lcv;	/* LCV to throttle loops */
	समय64_t		lcv_समय; /* Time loop was started */

	पूर्णांक			di_map[7]; /* Maps below items to live devs */
	काष्ठा hil_mlc_devinfo	di[HIL_MLC_DEVMEM];
	काष्ठा serio		*serio[HIL_MLC_DEVMEM];
	काष्ठा hil_mlc_serio_map serio_map[HIL_MLC_DEVMEM];
	hil_packet		serio_opacket[HIL_MLC_DEVMEM];
	पूर्णांक			serio_oidx[HIL_MLC_DEVMEM];
	काष्ठा hil_mlc_devinfo	di_scratch; /* Temporary area */

	पूर्णांक			opercnt;

	काष्ठा tasklet_काष्ठा	*tasklet;
पूर्ण;

पूर्णांक hil_mlc_रेजिस्टर(hil_mlc *mlc);
पूर्णांक hil_mlc_unरेजिस्टर(hil_mlc *mlc);
