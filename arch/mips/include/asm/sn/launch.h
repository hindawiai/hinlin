<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2000 by Colin Ngam
 */
#अगर_अघोषित _ASM_SN_LAUNCH_H
#घोषणा _ASM_SN_LAUNCH_H

#समावेश <यंत्र/sn/types.h>
#समावेश <यंत्र/sn/addrs.h>

/*
 * The launch data काष्ठाure resides at a fixed place in each node's memory
 * and is used to communicate between the master processor and the slave
 * processors.
 *
 * The master stores launch parameters in the launch काष्ठाure
 * corresponding to a target processor that is in a slave loop, then sends
 * an पूर्णांकerrupt to the slave processor.	 The slave calls the desired
 * function, then वापसs to the slave loop.  The master may poll or रुको
 * क्रम the slaves to finish.
 *
 * There is an array of launch काष्ठाures, one per CPU on the node.  One
 * पूर्णांकerrupt level is used per local CPU.
 */

#घोषणा LAUNCH_MAGIC		0xaddbead2addbead3
#अगर_घोषित CONFIG_SGI_IP27
#घोषणा LAUNCH_SIZखातापूर्ण		0x100
#घोषणा LAUNCH_PADSZ		0xa0
#पूर्ण_अगर

#घोषणा LAUNCH_OFF_MAGIC	0x00	/* Struct offsets क्रम assembly	    */
#घोषणा LAUNCH_OFF_BUSY		0x08
#घोषणा LAUNCH_OFF_CALL		0x10
#घोषणा LAUNCH_OFF_CALLC	0x18
#घोषणा LAUNCH_OFF_CALLPARM	0x20
#घोषणा LAUNCH_OFF_STACK	0x28
#घोषणा LAUNCH_OFF_GP		0x30
#घोषणा LAUNCH_OFF_BEVUTLB	0x38
#घोषणा LAUNCH_OFF_BEVNORMAL	0x40
#घोषणा LAUNCH_OFF_BEVECC	0x48

#घोषणा LAUNCH_STATE_DONE	0	/* Return value of LAUNCH_POLL	    */
#घोषणा LAUNCH_STATE_SENT	1
#घोषणा LAUNCH_STATE_RECD	2

/*
 * The launch routine is called only अगर the complement address is correct.
 *
 * Beक्रमe control is transferred to a routine, the complement address
 * is zeroed (invalidated) to prevent an accidental call from a spurious
 * पूर्णांकerrupt.
 *
 * The slave_launch routine turns on the BUSY flag, and the slave loop
 * clears the BUSY flag after control is वापसed to it.
 */

#अगर_अघोषित __ASSEMBLY__

प्रकार पूर्णांक launch_state_t;
प्रकार व्योम (*launch_proc_t)(u64 call_parm);

प्रकार काष्ठा launch_s अणु
	अस्थिर u64		magic;	/* Magic number			    */
	अस्थिर u64		busy;	/* Slave currently active	    */
	अस्थिर launch_proc_t	call_addr;	/* Func. क्रम slave to call  */
	अस्थिर u64		call_addr_c;	/* 1's complement of call_addr*/
	अस्थिर u64		call_parm;	/* Single parm passed to call*/
	अस्थिर व्योम *stack_addr;	/* Stack poपूर्णांकer क्रम slave function */
	अस्थिर व्योम *gp_addr;		/* Global poपूर्णांकer क्रम slave func.   */
	अस्थिर अक्षर		*bevutlb;/* Address of bev utlb ex handler   */
	अस्थिर अक्षर		*bevnormal;/*Address of bev normal ex handler */
	अस्थिर अक्षर		*bevecc;/* Address of bev cache err handler */
	अस्थिर अक्षर		pad[160];	/* Pad to LAUNCH_SIZखातापूर्ण	    */
पूर्ण launch_t;

/*
 * PROM entry poपूर्णांकs क्रम launch routines are determined by IPxxprom/start.s
 */

#घोषणा LAUNCH_SLAVE	(*(व्योम (*)(पूर्णांक nasid, पूर्णांक cpu, \
				    launch_proc_t call_addr, \
				    u64 call_parm, \
				    व्योम *stack_addr, \
				    व्योम *gp_addr)) \
			 IP27PROM_LAUNCHSLAVE)

#घोषणा LAUNCH_WAIT	(*(व्योम (*)(पूर्णांक nasid, पूर्णांक cpu, पूर्णांक समयout_msec)) \
			 IP27PROM_WAITSLAVE)

#घोषणा LAUNCH_POLL	(*(launch_state_t (*)(पूर्णांक nasid, पूर्णांक cpu)) \
			 IP27PROM_POLLSLAVE)

#घोषणा LAUNCH_LOOP	(*(व्योम (*)(व्योम)) \
			 IP27PROM_SLAVELOOP)

#घोषणा LAUNCH_FLASH	(*(व्योम (*)(व्योम)) \
			 IP27PROM_FLASHLEDS)

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_SN_LAUNCH_H */
