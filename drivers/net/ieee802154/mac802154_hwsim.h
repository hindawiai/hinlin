<शैली गुरु>
#अगर_अघोषित __MAC802154_HWSIM_H
#घोषणा __MAC802154_HWSIM_H

/* mac802154 hwsim netlink commands
 *
 * @MAC802154_HWSIM_CMD_UNSPEC: unspecअगरied command to catch error
 * @MAC802154_HWSIM_CMD_GET_RADIO: fetch inक्रमmation about existing radios
 * @MAC802154_HWSIM_CMD_SET_RADIO: change radio parameters during runसमय
 * @MAC802154_HWSIM_CMD_NEW_RADIO: create a new radio with the given parameters
 *	वापसs the radio ID (>= 0) or negative on errors, अगर successful
 *	then multicast the result
 * @MAC802154_HWSIM_CMD_DEL_RADIO: destroy a radio, reply is multicasted
 * @MAC802154_HWSIM_CMD_GET_EDGE: fetch inक्रमmation about existing edges
 * @MAC802154_HWSIM_CMD_SET_EDGE: change edge parameters during runसमय
 * @MAC802154_HWSIM_CMD_DEL_EDGE: delete edges between radios
 * @MAC802154_HWSIM_CMD_NEW_EDGE: create a new edge between two radios
 * @__MAC802154_HWSIM_CMD_MAX: क्रमागत limit
 */
क्रमागत अणु
	MAC802154_HWSIM_CMD_UNSPEC,

	MAC802154_HWSIM_CMD_GET_RADIO,
	MAC802154_HWSIM_CMD_SET_RADIO,
	MAC802154_HWSIM_CMD_NEW_RADIO,
	MAC802154_HWSIM_CMD_DEL_RADIO,

	MAC802154_HWSIM_CMD_GET_EDGE,
	MAC802154_HWSIM_CMD_SET_EDGE,
	MAC802154_HWSIM_CMD_DEL_EDGE,
	MAC802154_HWSIM_CMD_NEW_EDGE,

	__MAC802154_HWSIM_CMD_MAX,
पूर्ण;

#घोषणा MAC802154_HWSIM_CMD_MAX (__MAC802154_HWSIM_MAX - 1)

/* mac802154 hwsim netlink attributes
 *
 * @MAC802154_HWSIM_ATTR_UNSPEC: unspecअगरied attribute to catch error
 * @MAC802154_HWSIM_ATTR_RADIO_ID: u32 attribute to identअगरy the radio
 * @MAC802154_HWSIM_ATTR_EDGE: nested attribute of edges
 * @MAC802154_HWSIM_ATTR_EDGES: list अगर nested attributes which contains the
 *	edge inक्रमmation according the radio id
 * @__MAC802154_HWSIM_ATTR_MAX: क्रमागत limit
 */
क्रमागत अणु
	MAC802154_HWSIM_ATTR_UNSPEC,
	MAC802154_HWSIM_ATTR_RADIO_ID,
	MAC802154_HWSIM_ATTR_RADIO_EDGE,
	MAC802154_HWSIM_ATTR_RADIO_EDGES,
	__MAC802154_HWSIM_ATTR_MAX,
पूर्ण;

#घोषणा MAC802154_HWSIM_ATTR_MAX (__MAC802154_HWSIM_ATTR_MAX - 1)

/* mac802154 hwsim edge netlink attributes
 *
 * @MAC802154_HWSIM_EDGE_ATTR_UNSPEC: unspecअगरied attribute to catch error
 * @MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID: radio id where the edge poपूर्णांकs to
 * @MAC802154_HWSIM_EDGE_ATTR_LQI: LQI value which the endpoपूर्णांक radio will
 *	receive क्रम this edge
 * @__MAC802154_HWSIM_ATTR_MAX: क्रमागत limit
 */
क्रमागत अणु
	MAC802154_HWSIM_EDGE_ATTR_UNSPEC,
	MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID,
	MAC802154_HWSIM_EDGE_ATTR_LQI,
	__MAC802154_HWSIM_EDGE_ATTR_MAX,
पूर्ण;

#घोषणा MAC802154_HWSIM_EDGE_ATTR_MAX (__MAC802154_HWSIM_EDGE_ATTR_MAX - 1)

#पूर्ण_अगर /* __MAC802154_HWSIM_H */
