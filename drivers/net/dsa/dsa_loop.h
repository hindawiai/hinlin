<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DSA_LOOP_H
#घोषणा __DSA_LOOP_H

काष्ठा dsa_chip_data;

काष्ठा dsa_loop_pdata अणु
	/* Must be first, such that dsa_रेजिस्टर_चयन() can access this
	 * without gory poपूर्णांकer manipulations
	 */
	काष्ठा dsa_chip_data cd;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक enabled_ports;
	स्थिर अक्षर *netdev;
पूर्ण;

#घोषणा DSA_LOOP_NUM_PORTS	6
#घोषणा DSA_LOOP_CPU_PORT	(DSA_LOOP_NUM_PORTS - 1)

#पूर्ण_अगर /* __DSA_LOOP_H */
