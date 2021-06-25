<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_PSW_H
#घोषणा _PARISC_PSW_H

#घोषणा	PSW_I	0x00000001
#घोषणा	PSW_D	0x00000002
#घोषणा	PSW_P	0x00000004
#घोषणा	PSW_Q	0x00000008

#घोषणा	PSW_R	0x00000010
#घोषणा	PSW_F	0x00000020
#घोषणा	PSW_G	0x00000040	/* PA1.x only */
#घोषणा PSW_O	0x00000080	/* PA2.0 only */

/* ssm/rsm inकाष्ठाions number PSW_W and PSW_E dअगरferently */
#घोषणा PSW_SM_I	PSW_I	/* Enable External Interrupts */
#घोषणा PSW_SM_D	PSW_D
#घोषणा PSW_SM_P	PSW_P
#घोषणा PSW_SM_Q	PSW_Q	/* Enable Interrupt State Collection */
#घोषणा PSW_SM_R	PSW_R	/* Enable Recover Counter Trap */
#घोषणा PSW_SM_W	0x200	/* PA2.0 only : Enable Wide Mode */

#घोषणा PSW_SM_QUIET	PSW_SM_R+PSW_SM_Q+PSW_SM_P+PSW_SM_D+PSW_SM_I

#घोषणा PSW_CB	0x0000ff00

#घोषणा	PSW_M	0x00010000
#घोषणा	PSW_V	0x00020000
#घोषणा	PSW_C	0x00040000
#घोषणा	PSW_B	0x00080000

#घोषणा	PSW_X	0x00100000
#घोषणा	PSW_N	0x00200000
#घोषणा	PSW_L	0x00400000
#घोषणा	PSW_H	0x00800000

#घोषणा	PSW_T	0x01000000
#घोषणा	PSW_S	0x02000000
#घोषणा	PSW_E	0x04000000
#घोषणा PSW_W	0x08000000	/* PA2.0 only */
#घोषणा PSW_W_BIT       36      /* PA2.0 only */

#घोषणा	PSW_Z	0x40000000	/* PA1.x only */
#घोषणा	PSW_Y	0x80000000	/* PA1.x only */

#अगर_घोषित CONFIG_64BIT
#  define PSW_HI_CB 0x000000ff    /* PA2.0 only */
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#  define USER_PSW_HI_MASK	PSW_HI_CB
#  define WIDE_PSW		PSW_W
#अन्यथा 
#  define WIDE_PSW		0
#पूर्ण_अगर

/* Used when setting up क्रम rfi */
#घोषणा KERNEL_PSW    (WIDE_PSW | PSW_C | PSW_Q | PSW_P | PSW_D)
#घोषणा REAL_MODE_PSW (WIDE_PSW | PSW_Q)
#घोषणा USER_PSW_MASK (WIDE_PSW | PSW_T | PSW_N | PSW_X | PSW_B | PSW_V | PSW_CB)
#घोषणा USER_PSW      (PSW_C | PSW_Q | PSW_P | PSW_D | PSW_I)

#अगर_अघोषित __ASSEMBLY__

/* The program status word as bitfields.  */
काष्ठा pa_psw अणु
	अचिन्हित पूर्णांक y:1;
	अचिन्हित पूर्णांक z:1;
	अचिन्हित पूर्णांक rv:2;
	अचिन्हित पूर्णांक w:1;
	अचिन्हित पूर्णांक e:1;
	अचिन्हित पूर्णांक s:1;
	अचिन्हित पूर्णांक t:1;

	अचिन्हित पूर्णांक h:1;
	अचिन्हित पूर्णांक l:1;
	अचिन्हित पूर्णांक n:1;
	अचिन्हित पूर्णांक x:1;
	अचिन्हित पूर्णांक b:1;
	अचिन्हित पूर्णांक c:1;
	अचिन्हित पूर्णांक v:1;
	अचिन्हित पूर्णांक m:1;

	अचिन्हित पूर्णांक cb:8;

	अचिन्हित पूर्णांक o:1;
	अचिन्हित पूर्णांक g:1;
	अचिन्हित पूर्णांक f:1;
	अचिन्हित पूर्णांक r:1;
	अचिन्हित पूर्णांक q:1;
	अचिन्हित पूर्णांक p:1;
	अचिन्हित पूर्णांक d:1;
	अचिन्हित पूर्णांक i:1;
पूर्ण;

#अगर_घोषित CONFIG_64BIT
#घोषणा pa_psw(task) ((काष्ठा pa_psw *) ((अक्षर *) (task) + TASK_PT_PSW + 4))
#अन्यथा
#घोषणा pa_psw(task) ((काष्ठा pa_psw *) ((अक्षर *) (task) + TASK_PT_PSW))
#पूर्ण_अगर

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर
