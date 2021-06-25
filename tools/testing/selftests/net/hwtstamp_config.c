<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Test program क्रम SIOCअणुG,Sपूर्णHWTSTAMP
 * Copyright 2013 Solarflare Communications
 * Author: Ben Hutchings
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <sys/socket.h>
#समावेश <sys/ioctl.h>

#समावेश <linux/अगर.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/sockios.h>

अटल पूर्णांक
lookup_value(स्थिर अक्षर **names, पूर्णांक size, स्थिर अक्षर *name)
अणु
	पूर्णांक value;

	क्रम (value = 0; value < size; value++)
		अगर (names[value] && strहालcmp(names[value], name) == 0)
			वापस value;

	वापस -1;
पूर्ण

अटल स्थिर अक्षर *
lookup_name(स्थिर अक्षर **names, पूर्णांक size, पूर्णांक value)
अणु
	वापस (value >= 0 && value < size) ? names[value] : शून्य;
पूर्ण

अटल व्योम list_names(खाता *f, स्थिर अक्षर **names, पूर्णांक size)
अणु
	पूर्णांक value;

	क्रम (value = 0; value < size; value++)
		अगर (names[value])
			ख_लिखो(f, "    %s\n", names[value]);
पूर्ण

अटल स्थिर अक्षर *tx_types[] = अणु
#घोषणा TX_TYPE(name) [HWTSTAMP_TX_ ## name] = #name
	TX_TYPE(OFF),
	TX_TYPE(ON),
	TX_TYPE(ONESTEP_SYNC)
#अघोषित TX_TYPE
पूर्ण;
#घोषणा N_TX_TYPES ((पूर्णांक)(माप(tx_types) / माप(tx_types[0])))

अटल स्थिर अक्षर *rx_filters[] = अणु
#घोषणा RX_FILTER(name) [HWTSTAMP_FILTER_ ## name] = #name
	RX_FILTER(NONE),
	RX_FILTER(ALL),
	RX_FILTER(SOME),
	RX_FILTER(PTP_V1_L4_EVENT),
	RX_FILTER(PTP_V1_L4_SYNC),
	RX_FILTER(PTP_V1_L4_DELAY_REQ),
	RX_FILTER(PTP_V2_L4_EVENT),
	RX_FILTER(PTP_V2_L4_SYNC),
	RX_FILTER(PTP_V2_L4_DELAY_REQ),
	RX_FILTER(PTP_V2_L2_EVENT),
	RX_FILTER(PTP_V2_L2_SYNC),
	RX_FILTER(PTP_V2_L2_DELAY_REQ),
	RX_FILTER(PTP_V2_EVENT),
	RX_FILTER(PTP_V2_SYNC),
	RX_FILTER(PTP_V2_DELAY_REQ),
#अघोषित RX_FILTER
पूर्ण;
#घोषणा N_RX_FILTERS ((पूर्णांक)(माप(rx_filters) / माप(rx_filters[0])))

अटल व्योम usage(व्योम)
अणु
	ख_माला_दो("Usage: hwtstamp_config if_name [tx_type rx_filter]\n"
	      "tx_type is any of (case-insensitive):\n",
	      मानक_त्रुटि);
	list_names(मानक_त्रुटि, tx_types, N_TX_TYPES);
	ख_माला_दो("rx_filter is any of (case-insensitive):\n", मानक_त्रुटि);
	list_names(मानक_त्रुटि, rx_filters, N_RX_FILTERS);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा अगरreq अगरr;
	काष्ठा hwtstamp_config config;
	स्थिर अक्षर *name;
	पूर्णांक sock;

	अगर ((argc != 2 && argc != 4) || (म_माप(argv[1]) >= IFNAMSIZ)) अणु
		usage();
		वापस 2;
	पूर्ण

	अगर (argc == 4) अणु
		config.flags = 0;
		config.tx_type = lookup_value(tx_types, N_TX_TYPES, argv[2]);
		config.rx_filter = lookup_value(rx_filters, N_RX_FILTERS, argv[3]);
		अगर (config.tx_type < 0 || config.rx_filter < 0) अणु
			usage();
			वापस 2;
		पूर्ण
	पूर्ण

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	अगर (sock < 0) अणु
		लिखो_त्रुटि("socket");
		वापस 1;
	पूर्ण

	म_नकल(अगरr.अगरr_name, argv[1]);
	अगरr.अगरr_data = (caddr_t)&config;

	अगर (ioctl(sock, (argc == 2) ? SIOCGHWTSTAMP : SIOCSHWTSTAMP, &अगरr)) अणु
		लिखो_त्रुटि("ioctl");
		वापस 1;
	पूर्ण

	म_लिखो("flags = %#x\n", config.flags);
	name = lookup_name(tx_types, N_TX_TYPES, config.tx_type);
	अगर (name)
		म_लिखो("tx_type = %s\n", name);
	अन्यथा
		म_लिखो("tx_type = %d\n", config.tx_type);
	name = lookup_name(rx_filters, N_RX_FILTERS, config.rx_filter);
	अगर (name)
		म_लिखो("rx_filter = %s\n", name);
	अन्यथा
		म_लिखो("rx_filter = %d\n", config.rx_filter);

	वापस 0;
पूर्ण
