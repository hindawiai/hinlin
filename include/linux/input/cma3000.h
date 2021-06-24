<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VTI CMA3000_Dxx Accelerometer driver
 *
 * Copyright (C) 2010 Texas Instruments
 * Author: Hemanth V <hemanthv@ti.com>
 */

#अगर_अघोषित _LINUX_CMA3000_H
#घोषणा _LINUX_CMA3000_H

#घोषणा CMAMODE_DEFAULT    0
#घोषणा CMAMODE_MEAS100    1
#घोषणा CMAMODE_MEAS400    2
#घोषणा CMAMODE_MEAS40     3
#घोषणा CMAMODE_MOTDET     4
#घोषणा CMAMODE_FF100      5
#घोषणा CMAMODE_FF400      6
#घोषणा CMAMODE_POFF       7

#घोषणा CMARANGE_2G   2000
#घोषणा CMARANGE_8G   8000

/**
 * काष्ठा cma3000_i2c_platक्रमm_data - CMA3000 Platक्रमm data
 * @fuzz_x: Noise on X Axis
 * @fuzz_y: Noise on Y Axis
 * @fuzz_z: Noise on Z Axis
 * @g_range: G range in milli g i.e 2000 or 8000
 * @mode: Operating mode
 * @mdthr: Motion detect threshold value
 * @mdffपंचांगr: Motion detect and मुक्त fall समय value
 * @ffthr: Free fall threshold value
 */

काष्ठा cma3000_platक्रमm_data अणु
	पूर्णांक fuzz_x;
	पूर्णांक fuzz_y;
	पूर्णांक fuzz_z;
	पूर्णांक g_range;
	uपूर्णांक8_t mode;
	uपूर्णांक8_t mdthr;
	uपूर्णांक8_t mdffपंचांगr;
	uपूर्णांक8_t ffthr;
	अचिन्हित दीर्घ irqflags;
पूर्ण;

#पूर्ण_अगर
