<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASMARM_ARCH_OHCI_H
#घोषणा ASMARM_ARCH_OHCI_H

काष्ठा device;

काष्ठा pxaohci_platक्रमm_data अणु
	पूर्णांक (*init)(काष्ठा device *);
	व्योम (*निकास)(काष्ठा device *);

	अचिन्हित दीर्घ flags;
#घोषणा ENABLE_PORT1		(1 << 0)
#घोषणा ENABLE_PORT2		(1 << 1)
#घोषणा ENABLE_PORT3		(1 << 2)
#घोषणा ENABLE_PORT_ALL		(ENABLE_PORT1 | ENABLE_PORT2 | ENABLE_PORT3)

#घोषणा POWER_SENSE_LOW		(1 << 3)
#घोषणा POWER_CONTROL_LOW	(1 << 4)
#घोषणा NO_OC_PROTECTION	(1 << 5)
#घोषणा OC_MODE_GLOBAL		(0 << 6)
#घोषणा OC_MODE_PERPORT		(1 << 6)

	पूर्णांक घातer_on_delay;	/* Power On to Power Good समय - in ms
				 * HCD must रुको क्रम this duration beक्रमe
				 * accessing a घातered on port
				 */
	पूर्णांक port_mode;
#घोषणा PMM_NPS_MODE           1
#घोषणा PMM_GLOBAL_MODE        2
#घोषणा PMM_PERPORT_MODE       3

	पूर्णांक घातer_budget;
पूर्ण;

बाह्य व्योम pxa_set_ohci_info(काष्ठा pxaohci_platक्रमm_data *info);

#पूर्ण_अगर
