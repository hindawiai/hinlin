<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_X86_DEBUGREG_H
#घोषणा _UAPI_ASM_X86_DEBUGREG_H


/* Indicate the रेजिस्टर numbers क्रम a number of the specअगरic
   debug रेजिस्टरs.  Registers 0-3 contain the addresses we wish to trap on */
#घोषणा DR_FIRSTADDR 0        /* u_debugreg[DR_FIRSTADDR] */
#घोषणा DR_LASTADDR 3         /* u_debugreg[DR_LASTADDR]  */

#घोषणा DR_STATUS 6           /* u_debugreg[DR_STATUS]     */
#घोषणा DR_CONTROL 7          /* u_debugreg[DR_CONTROL] */

/* Define a few things क्रम the status रेजिस्टर.  We can use this to determine
   which debugging रेजिस्टर was responsible क्रम the trap.  The other bits
   are either reserved or not of पूर्णांकerest to us. */

/* Define reserved bits in DR6 which are always set to 1 */
#घोषणा DR6_RESERVED	(0xFFFF0FF0)

#घोषणा DR_TRAP0	(0x1)		/* db0 */
#घोषणा DR_TRAP1	(0x2)		/* db1 */
#घोषणा DR_TRAP2	(0x4)		/* db2 */
#घोषणा DR_TRAP3	(0x8)		/* db3 */
#घोषणा DR_TRAP_BITS	(DR_TRAP0|DR_TRAP1|DR_TRAP2|DR_TRAP3)

#घोषणा DR_BUS_LOCK	(0x800)		/* bus_lock */
#घोषणा DR_STEP		(0x4000)	/* single-step */
#घोषणा DR_SWITCH	(0x8000)	/* task चयन */

/* Now define a bunch of things क्रम manipulating the control रेजिस्टर.
   The top two bytes of the control रेजिस्टर consist of 4 fields of 4
   bits - each field corresponds to one of the four debug रेजिस्टरs,
   and indicates what types of access we trap on, and how large the data
   field is that we are looking at */

#घोषणा DR_CONTROL_SHIFT 16 /* Skip this many bits in ctl रेजिस्टर */
#घोषणा DR_CONTROL_SIZE 4   /* 4 control bits per रेजिस्टर */

#घोषणा DR_RW_EXECUTE (0x0)   /* Settings क्रम the access types to trap on */
#घोषणा DR_RW_WRITE (0x1)
#घोषणा DR_RW_READ (0x3)

#घोषणा DR_LEN_1 (0x0) /* Settings क्रम data length to trap on */
#घोषणा DR_LEN_2 (0x4)
#घोषणा DR_LEN_4 (0xC)
#घोषणा DR_LEN_8 (0x8)

/* The low byte to the control रेजिस्टर determine which रेजिस्टरs are
   enabled.  There are 4 fields of two bits.  One bit is "local", meaning
   that the processor will reset the bit after a task चयन and the other
   is global meaning that we have to explicitly reset the bit.  With linux,
   you can use either one, since we explicitly zero the रेजिस्टर when we enter
   kernel mode. */

#घोषणा DR_LOCAL_ENABLE_SHIFT 0    /* Extra shअगरt to the local enable bit */
#घोषणा DR_GLOBAL_ENABLE_SHIFT 1   /* Extra shअगरt to the global enable bit */
#घोषणा DR_LOCAL_ENABLE (0x1)      /* Local enable क्रम reg 0 */
#घोषणा DR_GLOBAL_ENABLE (0x2)     /* Global enable क्रम reg 0 */
#घोषणा DR_ENABLE_SIZE 2           /* 2 enable bits per रेजिस्टर */

#घोषणा DR_LOCAL_ENABLE_MASK (0x55)  /* Set  local bits क्रम all 4 regs */
#घोषणा DR_GLOBAL_ENABLE_MASK (0xAA) /* Set global bits क्रम all 4 regs */

/* The second byte to the control रेजिस्टर has a few special things.
   We can slow the inकाष्ठाion pipeline क्रम inकाष्ठाions coming via the
   gdt or the ldt अगर we want to.  I am not sure why this is an advantage */

#अगर_घोषित __i386__
#घोषणा DR_CONTROL_RESERVED (0xFC00) /* Reserved by Intel */
#अन्यथा
#घोषणा DR_CONTROL_RESERVED (0xFFFFFFFF0000FC00UL) /* Reserved */
#पूर्ण_अगर

#घोषणा DR_LOCAL_SLOWDOWN (0x100)   /* Local slow the pipeline */
#घोषणा DR_GLOBAL_SLOWDOWN (0x200)  /* Global slow the pipeline */

/*
 * HW अवरोधpoपूर्णांक additions
 */

#पूर्ण_अगर /* _UAPI_ASM_X86_DEBUGREG_H */
