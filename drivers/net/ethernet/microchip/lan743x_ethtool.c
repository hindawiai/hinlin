<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (C) 2018 Microchip Technology Inc. */

#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy.h>
#समावेश "lan743x_main.h"
#समावेश "lan743x_ethtool.h"

/* eeprom */
#घोषणा LAN743X_EEPROM_MAGIC		    (0x74A5)
#घोषणा LAN743X_OTP_MAGIC		    (0x74F3)
#घोषणा EEPROM_INDICATOR_1		    (0xA5)
#घोषणा EEPROM_INDICATOR_2		    (0xAA)
#घोषणा EEPROM_MAC_OFFSET		    (0x01)
#घोषणा MAX_EEPROM_SIZE			    (512)
#घोषणा MAX_OTP_SIZE			    (1024)
#घोषणा OTP_INDICATOR_1			    (0xF3)
#घोषणा OTP_INDICATOR_2			    (0xF7)

अटल पूर्णांक lan743x_otp_घातer_up(काष्ठा lan743x_adapter *adapter)
अणु
	u32 reg_value;

	reg_value = lan743x_csr_पढ़ो(adapter, OTP_PWR_DN);

	अगर (reg_value & OTP_PWR_DN_PWRDN_N_) अणु
		/* clear it and रुको to be cleared */
		reg_value &= ~OTP_PWR_DN_PWRDN_N_;
		lan743x_csr_ग_लिखो(adapter, OTP_PWR_DN, reg_value);

		usleep_range(100, 20000);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lan743x_otp_घातer_करोwn(काष्ठा lan743x_adapter *adapter)
अणु
	u32 reg_value;

	reg_value = lan743x_csr_पढ़ो(adapter, OTP_PWR_DN);
	अगर (!(reg_value & OTP_PWR_DN_PWRDN_N_)) अणु
		/* set घातer करोwn bit */
		reg_value |= OTP_PWR_DN_PWRDN_N_;
		lan743x_csr_ग_लिखो(adapter, OTP_PWR_DN, reg_value);
	पूर्ण
पूर्ण

अटल व्योम lan743x_otp_set_address(काष्ठा lan743x_adapter *adapter,
				    u32 address)
अणु
	lan743x_csr_ग_लिखो(adapter, OTP_ADDR_HIGH, (address >> 8) & 0x03);
	lan743x_csr_ग_लिखो(adapter, OTP_ADDR_LOW, address & 0xFF);
पूर्ण

अटल व्योम lan743x_otp_पढ़ो_go(काष्ठा lan743x_adapter *adapter)
अणु
	lan743x_csr_ग_लिखो(adapter, OTP_FUNC_CMD, OTP_FUNC_CMD_READ_);
	lan743x_csr_ग_लिखो(adapter, OTP_CMD_GO, OTP_CMD_GO_GO_);
पूर्ण

अटल पूर्णांक lan743x_otp_रुको_till_not_busy(काष्ठा lan743x_adapter *adapter)
अणु
	अचिन्हित दीर्घ समयout;
	u32 reg_val;

	समयout = jअगरfies + HZ;
	करो अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			netअगर_warn(adapter, drv, adapter->netdev,
				   "Timeout on OTP_STATUS completion\n");
			वापस -EIO;
		पूर्ण
		udelay(1);
		reg_val = lan743x_csr_पढ़ो(adapter, OTP_STATUS);
	पूर्ण जबतक (reg_val & OTP_STATUS_BUSY_);

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_otp_पढ़ो(काष्ठा lan743x_adapter *adapter, u32 offset,
			    u32 length, u8 *data)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	अगर (offset + length > MAX_OTP_SIZE)
		वापस -EINVAL;

	ret = lan743x_otp_घातer_up(adapter);
	अगर (ret < 0)
		वापस ret;

	ret = lan743x_otp_रुको_till_not_busy(adapter);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < length; i++) अणु
		lan743x_otp_set_address(adapter, offset + i);

		lan743x_otp_पढ़ो_go(adapter);
		ret = lan743x_otp_रुको_till_not_busy(adapter);
		अगर (ret < 0)
			वापस ret;
		data[i] = lan743x_csr_पढ़ो(adapter, OTP_READ_DATA);
	पूर्ण

	lan743x_otp_घातer_करोwn(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_otp_ग_लिखो(काष्ठा lan743x_adapter *adapter, u32 offset,
			     u32 length, u8 *data)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	अगर (offset + length > MAX_OTP_SIZE)
		वापस -EINVAL;

	ret = lan743x_otp_घातer_up(adapter);
	अगर (ret < 0)
		वापस ret;

	ret = lan743x_otp_रुको_till_not_busy(adapter);
	अगर (ret < 0)
		वापस ret;

	/* set to BYTE program mode */
	lan743x_csr_ग_लिखो(adapter, OTP_PRGM_MODE, OTP_PRGM_MODE_BYTE_);

	क्रम (i = 0; i < length; i++) अणु
		lan743x_otp_set_address(adapter, offset + i);

		lan743x_csr_ग_लिखो(adapter, OTP_PRGM_DATA, data[i]);
		lan743x_csr_ग_लिखो(adapter, OTP_TST_CMD, OTP_TST_CMD_PRGVRFY_);
		lan743x_csr_ग_लिखो(adapter, OTP_CMD_GO, OTP_CMD_GO_GO_);

		ret = lan743x_otp_रुको_till_not_busy(adapter);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	lan743x_otp_घातer_करोwn(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_eeprom_रुको(काष्ठा lan743x_adapter *adapter)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;

	करो अणु
		val = lan743x_csr_पढ़ो(adapter, E2P_CMD);

		अगर (!(val & E2P_CMD_EPC_BUSY_) ||
		    (val & E2P_CMD_EPC_TIMEOUT_))
			अवरोध;
		usleep_range(40, 100);
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	अगर (val & (E2P_CMD_EPC_TIMEOUT_ | E2P_CMD_EPC_BUSY_)) अणु
		netअगर_warn(adapter, drv, adapter->netdev,
			   "EEPROM read operation timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_eeprom_confirm_not_busy(काष्ठा lan743x_adapter *adapter)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;

	करो अणु
		val = lan743x_csr_पढ़ो(adapter, E2P_CMD);

		अगर (!(val & E2P_CMD_EPC_BUSY_))
			वापस 0;

		usleep_range(40, 100);
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	netअगर_warn(adapter, drv, adapter->netdev, "EEPROM is busy\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक lan743x_eeprom_पढ़ो(काष्ठा lan743x_adapter *adapter,
			       u32 offset, u32 length, u8 *data)
अणु
	पूर्णांक retval;
	u32 val;
	पूर्णांक i;

	अगर (offset + length > MAX_EEPROM_SIZE)
		वापस -EINVAL;

	retval = lan743x_eeprom_confirm_not_busy(adapter);
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < length; i++) अणु
		val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_READ_;
		val |= (offset & E2P_CMD_EPC_ADDR_MASK_);
		lan743x_csr_ग_लिखो(adapter, E2P_CMD, val);

		retval = lan743x_eeprom_रुको(adapter);
		अगर (retval < 0)
			वापस retval;

		val = lan743x_csr_पढ़ो(adapter, E2P_DATA);
		data[i] = val & 0xFF;
		offset++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_eeprom_ग_लिखो(काष्ठा lan743x_adapter *adapter,
				u32 offset, u32 length, u8 *data)
अणु
	पूर्णांक retval;
	u32 val;
	पूर्णांक i;

	अगर (offset + length > MAX_EEPROM_SIZE)
		वापस -EINVAL;

	retval = lan743x_eeprom_confirm_not_busy(adapter);
	अगर (retval)
		वापस retval;

	/* Issue ग_लिखो/erase enable command */
	val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_EWEN_;
	lan743x_csr_ग_लिखो(adapter, E2P_CMD, val);

	retval = lan743x_eeprom_रुको(adapter);
	अगर (retval < 0)
		वापस retval;

	क्रम (i = 0; i < length; i++) अणु
		/* Fill data रेजिस्टर */
		val = data[i];
		lan743x_csr_ग_लिखो(adapter, E2P_DATA, val);

		/* Send "write" command */
		val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_WRITE_;
		val |= (offset & E2P_CMD_EPC_ADDR_MASK_);
		lan743x_csr_ग_लिखो(adapter, E2P_CMD, val);

		retval = lan743x_eeprom_रुको(adapter);
		अगर (retval < 0)
			वापस retval;

		offset++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lan743x_ethtool_get_drvinfo(काष्ठा net_device *netdev,
					काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	strlcpy(info->driver, DRIVER_NAME, माप(info->driver));
	strlcpy(info->bus_info,
		pci_name(adapter->pdev), माप(info->bus_info));
पूर्ण

अटल u32 lan743x_ethtool_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	वापस adapter->msg_enable;
पूर्ण

अटल व्योम lan743x_ethtool_set_msglevel(काष्ठा net_device *netdev,
					 u32 msglevel)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	adapter->msg_enable = msglevel;
पूर्ण

अटल पूर्णांक lan743x_ethtool_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->flags & LAN743X_ADAPTER_FLAG_OTP)
		वापस MAX_OTP_SIZE;

	वापस MAX_EEPROM_SIZE;
पूर्ण

अटल पूर्णांक lan743x_ethtool_get_eeprom(काष्ठा net_device *netdev,
				      काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret = 0;

	अगर (adapter->flags & LAN743X_ADAPTER_FLAG_OTP)
		ret = lan743x_otp_पढ़ो(adapter, ee->offset, ee->len, data);
	अन्यथा
		ret = lan743x_eeprom_पढ़ो(adapter, ee->offset, ee->len, data);

	वापस ret;
पूर्ण

अटल पूर्णांक lan743x_ethtool_set_eeprom(काष्ठा net_device *netdev,
				      काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret = -EINVAL;

	अगर (adapter->flags & LAN743X_ADAPTER_FLAG_OTP) अणु
		/* Beware!  OTP is One Time Programming ONLY! */
		अगर (ee->magic == LAN743X_OTP_MAGIC) अणु
			ret = lan743x_otp_ग_लिखो(adapter, ee->offset,
						ee->len, data);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ee->magic == LAN743X_EEPROM_MAGIC) अणु
			ret = lan743x_eeprom_ग_लिखो(adapter, ee->offset,
						   ee->len, data);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर अक्षर lan743x_set0_hw_cnt_strings[][ETH_GSTRING_LEN] = अणु
	"RX FCS Errors",
	"RX Alignment Errors",
	"Rx Fragment Errors",
	"RX Jabber Errors",
	"RX Undersize Frame Errors",
	"RX Oversize Frame Errors",
	"RX Dropped Frames",
	"RX Unicast Byte Count",
	"RX Broadcast Byte Count",
	"RX Multicast Byte Count",
	"RX Unicast Frames",
	"RX Broadcast Frames",
	"RX Multicast Frames",
	"RX Pause Frames",
	"RX 64 Byte Frames",
	"RX 65 - 127 Byte Frames",
	"RX 128 - 255 Byte Frames",
	"RX 256 - 511 Bytes Frames",
	"RX 512 - 1023 Byte Frames",
	"RX 1024 - 1518 Byte Frames",
	"RX Greater 1518 Byte Frames",
पूर्ण;

अटल स्थिर अक्षर lan743x_set1_sw_cnt_strings[][ETH_GSTRING_LEN] = अणु
	"RX Queue 0 Frames",
	"RX Queue 1 Frames",
	"RX Queue 2 Frames",
	"RX Queue 3 Frames",
पूर्ण;

अटल स्थिर अक्षर lan743x_set2_hw_cnt_strings[][ETH_GSTRING_LEN] = अणु
	"RX Total Frames",
	"EEE RX LPI Transitions",
	"EEE RX LPI Time",
	"RX Counter Rollover Status",
	"TX FCS Errors",
	"TX Excess Deferral Errors",
	"TX Carrier Errors",
	"TX Bad Byte Count",
	"TX Single Collisions",
	"TX Multiple Collisions",
	"TX Excessive Collision",
	"TX Late Collisions",
	"TX Unicast Byte Count",
	"TX Broadcast Byte Count",
	"TX Multicast Byte Count",
	"TX Unicast Frames",
	"TX Broadcast Frames",
	"TX Multicast Frames",
	"TX Pause Frames",
	"TX 64 Byte Frames",
	"TX 65 - 127 Byte Frames",
	"TX 128 - 255 Byte Frames",
	"TX 256 - 511 Bytes Frames",
	"TX 512 - 1023 Byte Frames",
	"TX 1024 - 1518 Byte Frames",
	"TX Greater 1518 Byte Frames",
	"TX Total Frames",
	"EEE TX LPI Transitions",
	"EEE TX LPI Time",
	"TX Counter Rollover Status",
पूर्ण;

अटल स्थिर u32 lan743x_set0_hw_cnt_addr[] = अणु
	STAT_RX_FCS_ERRORS,
	STAT_RX_ALIGNMENT_ERRORS,
	STAT_RX_FRAGMENT_ERRORS,
	STAT_RX_JABBER_ERRORS,
	STAT_RX_UNDERSIZE_FRAME_ERRORS,
	STAT_RX_OVERSIZE_FRAME_ERRORS,
	STAT_RX_DROPPED_FRAMES,
	STAT_RX_UNICAST_BYTE_COUNT,
	STAT_RX_BROADCAST_BYTE_COUNT,
	STAT_RX_MULTICAST_BYTE_COUNT,
	STAT_RX_UNICAST_FRAMES,
	STAT_RX_BROADCAST_FRAMES,
	STAT_RX_MULTICAST_FRAMES,
	STAT_RX_PAUSE_FRAMES,
	STAT_RX_64_BYTE_FRAMES,
	STAT_RX_65_127_BYTE_FRAMES,
	STAT_RX_128_255_BYTE_FRAMES,
	STAT_RX_256_511_BYTES_FRAMES,
	STAT_RX_512_1023_BYTE_FRAMES,
	STAT_RX_1024_1518_BYTE_FRAMES,
	STAT_RX_GREATER_1518_BYTE_FRAMES,
पूर्ण;

अटल स्थिर u32 lan743x_set2_hw_cnt_addr[] = अणु
	STAT_RX_TOTAL_FRAMES,
	STAT_EEE_RX_LPI_TRANSITIONS,
	STAT_EEE_RX_LPI_TIME,
	STAT_RX_COUNTER_ROLLOVER_STATUS,
	STAT_TX_FCS_ERRORS,
	STAT_TX_EXCESS_DEFERRAL_ERRORS,
	STAT_TX_CARRIER_ERRORS,
	STAT_TX_BAD_BYTE_COUNT,
	STAT_TX_SINGLE_COLLISIONS,
	STAT_TX_MULTIPLE_COLLISIONS,
	STAT_TX_EXCESSIVE_COLLISION,
	STAT_TX_LATE_COLLISIONS,
	STAT_TX_UNICAST_BYTE_COUNT,
	STAT_TX_BROADCAST_BYTE_COUNT,
	STAT_TX_MULTICAST_BYTE_COUNT,
	STAT_TX_UNICAST_FRAMES,
	STAT_TX_BROADCAST_FRAMES,
	STAT_TX_MULTICAST_FRAMES,
	STAT_TX_PAUSE_FRAMES,
	STAT_TX_64_BYTE_FRAMES,
	STAT_TX_65_127_BYTE_FRAMES,
	STAT_TX_128_255_BYTE_FRAMES,
	STAT_TX_256_511_BYTES_FRAMES,
	STAT_TX_512_1023_BYTE_FRAMES,
	STAT_TX_1024_1518_BYTE_FRAMES,
	STAT_TX_GREATER_1518_BYTE_FRAMES,
	STAT_TX_TOTAL_FRAMES,
	STAT_EEE_TX_LPI_TRANSITIONS,
	STAT_EEE_TX_LPI_TIME,
	STAT_TX_COUNTER_ROLLOVER_STATUS
पूर्ण;

अटल स्थिर अक्षर lan743x_priv_flags_strings[][ETH_GSTRING_LEN] = अणु
	"OTP_ACCESS",
पूर्ण;

अटल व्योम lan743x_ethtool_get_strings(काष्ठा net_device *netdev,
					u32 stringset, u8 *data)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, lan743x_set0_hw_cnt_strings,
		       माप(lan743x_set0_hw_cnt_strings));
		स_नकल(&data[माप(lan743x_set0_hw_cnt_strings)],
		       lan743x_set1_sw_cnt_strings,
		       माप(lan743x_set1_sw_cnt_strings));
		स_नकल(&data[माप(lan743x_set0_hw_cnt_strings) +
		       माप(lan743x_set1_sw_cnt_strings)],
		       lan743x_set2_hw_cnt_strings,
		       माप(lan743x_set2_hw_cnt_strings));
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(data, lan743x_priv_flags_strings,
		       माप(lan743x_priv_flags_strings));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम lan743x_ethtool_get_ethtool_stats(काष्ठा net_device *netdev,
					      काष्ठा ethtool_stats *stats,
					      u64 *data)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	पूर्णांक data_index = 0;
	u32 buf;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lan743x_set0_hw_cnt_addr); i++) अणु
		buf = lan743x_csr_पढ़ो(adapter, lan743x_set0_hw_cnt_addr[i]);
		data[data_index++] = (u64)buf;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(adapter->rx); i++)
		data[data_index++] = (u64)(adapter->rx[i].frame_count);
	क्रम (i = 0; i < ARRAY_SIZE(lan743x_set2_hw_cnt_addr); i++) अणु
		buf = lan743x_csr_पढ़ो(adapter, lan743x_set2_hw_cnt_addr[i]);
		data[data_index++] = (u64)buf;
	पूर्ण
पूर्ण

अटल u32 lan743x_ethtool_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	वापस adapter->flags;
पूर्ण

अटल पूर्णांक lan743x_ethtool_set_priv_flags(काष्ठा net_device *netdev, u32 flags)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	adapter->flags = flags;

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ethtool_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
	अणु
		पूर्णांक ret;

		ret = ARRAY_SIZE(lan743x_set0_hw_cnt_strings);
		ret += ARRAY_SIZE(lan743x_set1_sw_cnt_strings);
		ret += ARRAY_SIZE(lan743x_set2_hw_cnt_strings);
		वापस ret;
	पूर्ण
	हाल ETH_SS_PRIV_FLAGS:
		वापस ARRAY_SIZE(lan743x_priv_flags_strings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lan743x_ethtool_get_rxnfc(काष्ठा net_device *netdev,
				     काष्ठा ethtool_rxnfc *rxnfc,
				     u32 *rule_locs)
अणु
	चयन (rxnfc->cmd) अणु
	हाल ETHTOOL_GRXFH:
		rxnfc->data = 0;
		चयन (rxnfc->flow_type) अणु
		हाल TCP_V4_FLOW:हाल UDP_V4_FLOW:
		हाल TCP_V6_FLOW:हाल UDP_V6_FLOW:
			rxnfc->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
			fallthrough;
		हाल IPV4_FLOW: हाल IPV6_FLOW:
			rxnfc->data |= RXH_IP_SRC | RXH_IP_DST;
			वापस 0;
		पूर्ण
		अवरोध;
	हाल ETHTOOL_GRXRINGS:
		rxnfc->data = LAN743X_USED_RX_CHANNELS;
		वापस 0;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल u32 lan743x_ethtool_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस 40;
पूर्ण

अटल u32 lan743x_ethtool_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	वापस 128;
पूर्ण

अटल पूर्णांक lan743x_ethtool_get_rxfh(काष्ठा net_device *netdev,
				    u32 *indir, u8 *key, u8 *hfunc)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	अगर (indir) अणु
		पूर्णांक dw_index;
		पूर्णांक byte_index = 0;

		क्रम (dw_index = 0; dw_index < 32; dw_index++) अणु
			u32 four_entries =
				lan743x_csr_पढ़ो(adapter, RFE_INDX(dw_index));

			byte_index = dw_index << 2;
			indir[byte_index + 0] =
				((four_entries >> 0) & 0x000000FF);
			indir[byte_index + 1] =
				((four_entries >> 8) & 0x000000FF);
			indir[byte_index + 2] =
				((four_entries >> 16) & 0x000000FF);
			indir[byte_index + 3] =
				((four_entries >> 24) & 0x000000FF);
		पूर्ण
	पूर्ण
	अगर (key) अणु
		पूर्णांक dword_index;
		पूर्णांक byte_index = 0;

		क्रम (dword_index = 0; dword_index < 10; dword_index++) अणु
			u32 four_entries =
				lan743x_csr_पढ़ो(adapter,
						 RFE_HASH_KEY(dword_index));

			byte_index = dword_index << 2;
			key[byte_index + 0] =
				((four_entries >> 0) & 0x000000FF);
			key[byte_index + 1] =
				((four_entries >> 8) & 0x000000FF);
			key[byte_index + 2] =
				((four_entries >> 16) & 0x000000FF);
			key[byte_index + 3] =
				((four_entries >> 24) & 0x000000FF);
		पूर्ण
	पूर्ण
	अगर (hfunc)
		(*hfunc) = ETH_RSS_HASH_TOP;
	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ethtool_set_rxfh(काष्ठा net_device *netdev,
				    स्थिर u32 *indir, स्थिर u8 *key,
				    स्थिर u8 hfunc)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	अगर (indir) अणु
		u32 indir_value = 0;
		पूर्णांक dword_index = 0;
		पूर्णांक byte_index = 0;

		क्रम (dword_index = 0; dword_index < 32; dword_index++) अणु
			byte_index = dword_index << 2;
			indir_value =
				(((indir[byte_index + 0] & 0x000000FF) << 0) |
				((indir[byte_index + 1] & 0x000000FF) << 8) |
				((indir[byte_index + 2] & 0x000000FF) << 16) |
				((indir[byte_index + 3] & 0x000000FF) << 24));
			lan743x_csr_ग_लिखो(adapter, RFE_INDX(dword_index),
					  indir_value);
		पूर्ण
	पूर्ण
	अगर (key) अणु
		पूर्णांक dword_index = 0;
		पूर्णांक byte_index = 0;
		u32 key_value = 0;

		क्रम (dword_index = 0; dword_index < 10; dword_index++) अणु
			byte_index = dword_index << 2;
			key_value =
				((((u32)(key[byte_index + 0])) << 0) |
				(((u32)(key[byte_index + 1])) << 8) |
				(((u32)(key[byte_index + 2])) << 16) |
				(((u32)(key[byte_index + 3])) << 24));
			lan743x_csr_ग_लिखो(adapter, RFE_HASH_KEY(dword_index),
					  key_value);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ethtool_get_ts_info(काष्ठा net_device *netdev,
				       काष्ठा ethtool_ts_info *ts_info)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	ts_info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				   SOF_TIMESTAMPING_RX_SOFTWARE |
				   SOF_TIMESTAMPING_SOFTWARE |
				   SOF_TIMESTAMPING_TX_HARDWARE |
				   SOF_TIMESTAMPING_RX_HARDWARE |
				   SOF_TIMESTAMPING_RAW_HARDWARE;

	अगर (adapter->ptp.ptp_घड़ी)
		ts_info->phc_index = ptp_घड़ी_index(adapter->ptp.ptp_घड़ी);
	अन्यथा
		ts_info->phc_index = -1;

	ts_info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			    BIT(HWTSTAMP_TX_ON) |
			    BIT(HWTSTAMP_TX_ONESTEP_SYNC);
	ts_info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) |
			      BIT(HWTSTAMP_FILTER_ALL);
	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ethtool_get_eee(काष्ठा net_device *netdev,
				   काष्ठा ethtool_eee *eee)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	काष्ठा phy_device *phydev = netdev->phydev;
	u32 buf;
	पूर्णांक ret;

	अगर (!phydev)
		वापस -EIO;
	अगर (!phydev->drv) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "Missing PHY Driver\n");
		वापस -EIO;
	पूर्ण

	ret = phy_ethtool_get_eee(phydev, eee);
	अगर (ret < 0)
		वापस ret;

	buf = lan743x_csr_पढ़ो(adapter, MAC_CR);
	अगर (buf & MAC_CR_EEE_EN_) अणु
		eee->eee_enabled = true;
		eee->eee_active = !!(eee->advertised & eee->lp_advertised);
		eee->tx_lpi_enabled = true;
		/* EEE_TX_LPI_REQ_DLY & tx_lpi_समयr are same uSec unit */
		buf = lan743x_csr_पढ़ो(adapter, MAC_EEE_TX_LPI_REQ_DLY_CNT);
		eee->tx_lpi_समयr = buf;
	पूर्ण अन्यथा अणु
		eee->eee_enabled = false;
		eee->eee_active = false;
		eee->tx_lpi_enabled = false;
		eee->tx_lpi_समयr = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ethtool_set_eee(काष्ठा net_device *netdev,
				   काष्ठा ethtool_eee *eee)
अणु
	काष्ठा lan743x_adapter *adapter;
	काष्ठा phy_device *phydev;
	u32 buf = 0;
	पूर्णांक ret = 0;

	अगर (!netdev)
		वापस -EINVAL;
	adapter = netdev_priv(netdev);
	अगर (!adapter)
		वापस -EINVAL;
	phydev = netdev->phydev;
	अगर (!phydev)
		वापस -EIO;
	अगर (!phydev->drv) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "Missing PHY Driver\n");
		वापस -EIO;
	पूर्ण

	अगर (eee->eee_enabled) अणु
		ret = phy_init_eee(phydev, 0);
		अगर (ret) अणु
			netअगर_err(adapter, drv, adapter->netdev,
				  "EEE initialization failed\n");
			वापस ret;
		पूर्ण

		buf = (u32)eee->tx_lpi_समयr;
		lan743x_csr_ग_लिखो(adapter, MAC_EEE_TX_LPI_REQ_DLY_CNT, buf);

		buf = lan743x_csr_पढ़ो(adapter, MAC_CR);
		buf |= MAC_CR_EEE_EN_;
		lan743x_csr_ग_लिखो(adapter, MAC_CR, buf);
	पूर्ण अन्यथा अणु
		buf = lan743x_csr_पढ़ो(adapter, MAC_CR);
		buf &= ~MAC_CR_EEE_EN_;
		lan743x_csr_ग_लिखो(adapter, MAC_CR, buf);
	पूर्ण

	वापस phy_ethtool_set_eee(phydev, eee);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम lan743x_ethtool_get_wol(काष्ठा net_device *netdev,
				    काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	wol->supported = 0;
	wol->wolopts = 0;

	अगर (netdev->phydev)
		phy_ethtool_get_wol(netdev->phydev, wol);

	wol->supported |= WAKE_BCAST | WAKE_UCAST | WAKE_MCAST |
		WAKE_MAGIC | WAKE_PHY | WAKE_ARP;

	wol->wolopts |= adapter->wolopts;
पूर्ण

अटल पूर्णांक lan743x_ethtool_set_wol(काष्ठा net_device *netdev,
				   काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	adapter->wolopts = 0;
	अगर (wol->wolopts & WAKE_UCAST)
		adapter->wolopts |= WAKE_UCAST;
	अगर (wol->wolopts & WAKE_MCAST)
		adapter->wolopts |= WAKE_MCAST;
	अगर (wol->wolopts & WAKE_BCAST)
		adapter->wolopts |= WAKE_BCAST;
	अगर (wol->wolopts & WAKE_MAGIC)
		adapter->wolopts |= WAKE_MAGIC;
	अगर (wol->wolopts & WAKE_PHY)
		adapter->wolopts |= WAKE_PHY;
	अगर (wol->wolopts & WAKE_ARP)
		adapter->wolopts |= WAKE_ARP;

	device_set_wakeup_enable(&adapter->pdev->dev, (bool)wol->wolopts);

	वापस netdev->phydev ? phy_ethtool_set_wol(netdev->phydev, wol)
			: -ENETDOWN;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

स्थिर काष्ठा ethtool_ops lan743x_ethtool_ops = अणु
	.get_drvinfo = lan743x_ethtool_get_drvinfo,
	.get_msglevel = lan743x_ethtool_get_msglevel,
	.set_msglevel = lan743x_ethtool_set_msglevel,
	.get_link = ethtool_op_get_link,

	.get_eeprom_len = lan743x_ethtool_get_eeprom_len,
	.get_eeprom = lan743x_ethtool_get_eeprom,
	.set_eeprom = lan743x_ethtool_set_eeprom,
	.get_strings = lan743x_ethtool_get_strings,
	.get_ethtool_stats = lan743x_ethtool_get_ethtool_stats,
	.get_priv_flags = lan743x_ethtool_get_priv_flags,
	.set_priv_flags = lan743x_ethtool_set_priv_flags,
	.get_sset_count = lan743x_ethtool_get_sset_count,
	.get_rxnfc = lan743x_ethtool_get_rxnfc,
	.get_rxfh_key_size = lan743x_ethtool_get_rxfh_key_size,
	.get_rxfh_indir_size = lan743x_ethtool_get_rxfh_indir_size,
	.get_rxfh = lan743x_ethtool_get_rxfh,
	.set_rxfh = lan743x_ethtool_set_rxfh,
	.get_ts_info = lan743x_ethtool_get_ts_info,
	.get_eee = lan743x_ethtool_get_eee,
	.set_eee = lan743x_ethtool_set_eee,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
#अगर_घोषित CONFIG_PM
	.get_wol = lan743x_ethtool_get_wol,
	.set_wol = lan743x_ethtool_set_wol,
#पूर्ण_अगर
पूर्ण;
