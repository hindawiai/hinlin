<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DSA_PDATA_H
#घोषणा __DSA_PDATA_H

काष्ठा device;
काष्ठा net_device;

#घोषणा DSA_MAX_SWITCHES	4
#घोषणा DSA_MAX_PORTS		12
#घोषणा DSA_RTABLE_NONE		-1

काष्ठा dsa_chip_data अणु
	/*
	 * How to access the चयन configuration रेजिस्टरs.
	 */
	काष्ठा device	*host_dev;
	पूर्णांक		sw_addr;

	/*
	 * Reference to network devices
	 */
	काष्ठा device	*netdev[DSA_MAX_PORTS];

	/* set to size of eeprom अगर supported by the चयन */
	पूर्णांक		eeprom_len;

	/* Device tree node poपूर्णांकer क्रम this specअगरic चयन chip
	 * used during चयन setup in हाल additional properties
	 * and resources needs to be used
	 */
	काष्ठा device_node *of_node;

	/*
	 * The names of the चयन's ports.  Use "cpu" to
	 * designate the चयन port that the cpu is connected to,
	 * "dsa" to indicate that this port is a DSA link to
	 * another चयन, शून्य to indicate the port is unused,
	 * or any other string to indicate this is a physical port.
	 */
	अक्षर		*port_names[DSA_MAX_PORTS];
	काष्ठा device_node *port_dn[DSA_MAX_PORTS];

	/*
	 * An array of which element [a] indicates which port on this
	 * चयन should be used to send packets to that are destined
	 * क्रम चयन a. Can be शून्य अगर there is only one चयन chip.
	 */
	s8		rtable[DSA_MAX_SWITCHES];
पूर्ण;

काष्ठा dsa_platक्रमm_data अणु
	/*
	 * Reference to a Linux network पूर्णांकerface that connects
	 * to the root चयन chip of the tree.
	 */
	काष्ठा device	*netdev;
	काष्ठा net_device *of_netdev;

	/*
	 * Info काष्ठाs describing each of the चयन chips
	 * connected via this network पूर्णांकerface.
	 */
	पूर्णांक		nr_chips;
	काष्ठा dsa_chip_data	*chip;
पूर्ण;


#पूर्ण_अगर /* __DSA_PDATA_H */
