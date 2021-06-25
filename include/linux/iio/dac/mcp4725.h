<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * MCP4725 DAC driver
 *
 * Copyright (C) 2012 Peter Meerwald <pmeerw@pmeerw.net>
 */

#अगर_अघोषित IIO_DAC_MCP4725_H_
#घोषणा IIO_DAC_MCP4725_H_

/**
 * काष्ठा mcp4725_platक्रमm_data - MCP4725/6 DAC specअगरic data.
 * @use_vref: Whether an बाह्यal reference voltage on Vref pin should be used.
 *            Additional vref-supply must be specअगरied when used.
 * @vref_buffered: Controls buffering of the बाह्यal reference voltage.
 *
 * Vref related settings are available only on MCP4756. See
 * Documentation/devicetree/bindings/iio/dac/microchip,mcp4725.yaml क्रम more inक्रमmation.
 */
काष्ठा mcp4725_platक्रमm_data अणु
	bool use_vref;
	bool vref_buffered;
पूर्ण;

#पूर्ण_अगर /* IIO_DAC_MCP4725_H_ */
