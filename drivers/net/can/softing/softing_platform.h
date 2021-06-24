<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश <linux/platक्रमm_device.h>

#अगर_अघोषित _SOFTING_DEVICE_H_
#घोषणा _SOFTING_DEVICE_H_

/* softing firmware directory prefix */
#घोषणा fw_dir "softing-4.6/"

काष्ठा softing_platक्रमm_data अणु
	अचिन्हित पूर्णांक manf;
	अचिन्हित पूर्णांक prod;
	/*
	 * generation
	 * 1st with NEC or SJA1000
	 * 8bit, exclusive पूर्णांकerrupt, ...
	 * 2nd only SJA1000
	 * 16bit, shared पूर्णांकerrupt
	 */
	पूर्णांक generation;
	पूर्णांक nbus; /* # buses on device */
	अचिन्हित पूर्णांक freq; /* operating frequency in Hz */
	अचिन्हित पूर्णांक max_brp;
	अचिन्हित पूर्णांक max_sjw;
	अचिन्हित दीर्घ dpram_size;
	स्थिर अक्षर *name;
	काष्ठा अणु
		अचिन्हित दीर्घ offs;
		अचिन्हित दीर्घ addr;
		स्थिर अक्षर *fw;
	पूर्ण boot, load, app;
	/*
	 * reset() function
	 * bring pdev in or out of reset, depending on value
	 */
	पूर्णांक (*reset)(काष्ठा platक्रमm_device *pdev, पूर्णांक value);
	पूर्णांक (*enable_irq)(काष्ठा platक्रमm_device *pdev, पूर्णांक value);
पूर्ण;

#पूर्ण_अगर
