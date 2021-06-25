<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __nosy_dump_h__
#घोषणा __nosy_dump_h__

#घोषणा array_length(array) (माप(array) / माप(array[0]))

#घोषणा ACK_NO_ACK   0x0
#घोषणा ACK_DONE(a)  ((a >> 2) == 0)
#घोषणा ACK_BUSY(a)  ((a >> 2) == 1)
#घोषणा ACK_ERROR(a) ((a >> 2) == 3)

#समावेश <मानक_निवेशt.h>

काष्ठा phy_packet अणु
	uपूर्णांक32_t बारtamp;
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t zero:24;
			uपूर्णांक32_t phy_id:6;
			uपूर्णांक32_t identअगरier:2;
		पूर्ण common, link_on;

		काष्ठा अणु
			uपूर्णांक32_t zero:16;
			uपूर्णांक32_t gap_count:6;
			uपूर्णांक32_t set_gap_count:1;
			uपूर्णांक32_t set_root:1;
			uपूर्णांक32_t root_id:6;
			uपूर्णांक32_t identअगरier:2;
		पूर्ण phy_config;

		काष्ठा अणु
			uपूर्णांक32_t more_packets:1;
			uपूर्णांक32_t initiated_reset:1;
			uपूर्णांक32_t port2:2;
			uपूर्णांक32_t port1:2;
			uपूर्णांक32_t port0:2;
			uपूर्णांक32_t घातer_class:3;
			uपूर्णांक32_t contender:1;
			uपूर्णांक32_t phy_delay:2;
			uपूर्णांक32_t phy_speed:2;
			uपूर्णांक32_t gap_count:6;
			uपूर्णांक32_t link_active:1;
			uपूर्णांक32_t extended:1;
			uपूर्णांक32_t phy_id:6;
			uपूर्णांक32_t identअगरier:2;
		पूर्ण self_id;

		काष्ठा अणु
			uपूर्णांक32_t more_packets:1;
			uपूर्णांक32_t reserved1:1;
			uपूर्णांक32_t porth:2;
			uपूर्णांक32_t portg:2;
			uपूर्णांक32_t portf:2;
			uपूर्णांक32_t porte:2;
			uपूर्णांक32_t portd:2;
			uपूर्णांक32_t portc:2;
			uपूर्णांक32_t portb:2;
			uपूर्णांक32_t porta:2;
			uपूर्णांक32_t reserved0:2;
			uपूर्णांक32_t sequence:3;
			uपूर्णांक32_t extended:1;
			uपूर्णांक32_t phy_id:6;
			uपूर्णांक32_t identअगरier:2;
		पूर्ण ext_self_id;
	पूर्ण;
	uपूर्णांक32_t inverted;
	uपूर्णांक32_t ack;
पूर्ण;

#घोषणा TCODE_PHY_PACKET 0x10

#घोषणा PHY_PACKET_CONFIGURATION 0x00
#घोषणा PHY_PACKET_LINK_ON 0x01
#घोषणा PHY_PACKET_SELF_ID 0x02

काष्ठा link_packet अणु
	uपूर्णांक32_t बारtamp;
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t priority:4;
			uपूर्णांक32_t tcode:4;
			uपूर्णांक32_t rt:2;
			uपूर्णांक32_t tlabel:6;
			uपूर्णांक32_t destination:16;

			uपूर्णांक32_t offset_high:16;
			uपूर्णांक32_t source:16;

			uपूर्णांक32_t offset_low;
		पूर्ण common;

		काष्ठा अणु
			uपूर्णांक32_t common[3];
			uपूर्णांक32_t crc;
		पूर्ण पढ़ो_quadlet;

		काष्ठा अणु
			uपूर्णांक32_t common[3];
			uपूर्णांक32_t data;
			uपूर्णांक32_t crc;
		पूर्ण पढ़ो_quadlet_response;

		काष्ठा अणु
			uपूर्णांक32_t common[3];
			uपूर्णांक32_t extended_tcode:16;
			uपूर्णांक32_t data_length:16;
			uपूर्णांक32_t crc;
		पूर्ण पढ़ो_block;

		काष्ठा अणु
			uपूर्णांक32_t common[3];
			uपूर्णांक32_t extended_tcode:16;
			uपूर्णांक32_t data_length:16;
			uपूर्णांक32_t crc;
			uपूर्णांक32_t data[0];
			/* crc and ack follows. */
		पूर्ण पढ़ो_block_response;

		काष्ठा अणु
			uपूर्णांक32_t common[3];
			uपूर्णांक32_t data;
			uपूर्णांक32_t crc;
		पूर्ण ग_लिखो_quadlet;

		काष्ठा अणु
			uपूर्णांक32_t common[3];
			uपूर्णांक32_t extended_tcode:16;
			uपूर्णांक32_t data_length:16;
			uपूर्णांक32_t crc;
			uपूर्णांक32_t data[0];
			/* crc and ack follows. */
		पूर्ण ग_लिखो_block;

		काष्ठा अणु
			uपूर्णांक32_t common[3];
			uपूर्णांक32_t crc;
		पूर्ण ग_लिखो_response;

		काष्ठा अणु
			uपूर्णांक32_t common[3];
			uपूर्णांक32_t data;
			uपूर्णांक32_t crc;
		पूर्ण cycle_start;

		काष्ठा अणु
			uपूर्णांक32_t sy:4;
			uपूर्णांक32_t tcode:4;
			uपूर्णांक32_t channel:6;
			uपूर्णांक32_t tag:2;
			uपूर्णांक32_t data_length:16;

			uपूर्णांक32_t crc;
		पूर्ण iso_data;
	पूर्ण;
पूर्ण;

काष्ठा subaction अणु
	uपूर्णांक32_t ack;
	माप_प्रकार length;
	काष्ठा list link;
	काष्ठा link_packet packet;
पूर्ण;

काष्ठा link_transaction अणु
	पूर्णांक request_node, response_node, tlabel;
	काष्ठा subaction *request, *response;
	काष्ठा list request_list, response_list;
	काष्ठा list link;
पूर्ण;

पूर्णांक decode_fcp(काष्ठा link_transaction *t);

#पूर्ण_अगर /* __nosy_dump_h__ */
