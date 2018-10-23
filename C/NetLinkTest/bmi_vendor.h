/*
 * Copyright (c) 2017 Blu Wireless Technology
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
 * This implementation of the Blu Wireless MAC Interface (BMI) is
 * based on the Qualcom Atheros Wilocity 6210 Linux kernel driver.
 */

/*
 * This file contains the nl80211 vendor command definitions of the BWT Mac.
 *
 * Structures defined in here need to be packed, as they are transported
 * across the nl80211 interface as byte arrays.
 */

#ifndef __BMI_VENDOR_H__
#define __BMI_VENDOR_H__

#define BWT_OUI 0x681f40

#define BMI_MAC_LEN (6)
#define	BMI_NUM_TID (4) //!< TIDs per STA
#define CIR_DATA_LEN (128)
#define BMI_NUM_RX_DC_OFFSET_ENTRIES (256)
#define	BMI_NUM_EQ_FILTER_TAPS (14)
#define BMI_MAX_CHANNELS (8)
#define	BMI_EVENT_DATA_WORDS (16)

/* List of vendor command sub-cmds. This index is passed as the sub-command
 * parameter on the command line to iw.
 */
enum bh2_vendor_commands {
	BH2_GET_STATISTICS = 0x0,
	BH2_SET_MCS_MODE = 0x1,
	BH2_SET_AMSDU_PARAMS = 0x2,
	BH2_SET_TRANSMIT_CONFIG = 0x3,
	BH2_SET_SCHEDULING_PARAMS = 0x4,
	BH2_SET_BEAM_INDICIES = 0x5,
	BH2_SET_RX_GAIN = 0x6,
	BH2_SET_BEACON_PARAMETERS = 0x7,
	BH2_CLEAR_BEAM_INDICES = 0x8,
	BH2_CLEAR_SCHEDULING_PARAMS = 0x9,
	BH2_STA_BA_ENABLE = 0xa,
	BH2_STA_BA_DISABLE = 0xb,
	BH2_GET_MCS_MODE = 0xc,
	BH2_GET_AMSDU_PARAMS = 0xd,
	BH2_GET_SCHEDULING_PARAMS = 0xe,
	BH2_SET_CHANNEL_PARAMS = 0xf,
	BH2_GET_FIRMWARE_VERSION = 0x10,
	BH2_SET_STA_DMG_CAPABILITIES = 0x11,
	BH2_SET_MAX_LOST_BEACONS = 0x12,
	BH2_GET_PHY_PARAMS = 0x13,
	BH2_SET_PHY_PARAMS = 0x14,
	BH2_GET_RADIO_PARAMS = 0x15,
	BH2_SET_RADIO_PARAMS = 0x16,
	BH2_SET_ATI_CONFIG = 0x17,
	BH2_SET_LINK_ADAPTATION = 0x18,
	BH2_SET_LINK_MEASUREMENT_PERIOD = 0x19,
	BH2_SET_CIR_CAPTURE = 0x1a,
	BH2_SET_SCHEDULING_MODE = 0x1b,
	BH2_GET_SCHEDULING_MODE = 0x1c,
	BH2_SET_ABFT_CONFIGURATION = 0x1d,
	BH2_GET_ABFT_CONFIGURATION = 0x1e,
	BH2_GET_STA_PHY_ANALYSIS_DATA = 0x1f,
	BH2_SET_TIMING_ADVANCE = 0x20,
	BH2_SET_BEAM_BOOK = 0x21,
	BH2_SET_STD = 0x22,
	BH2_SET_TEST_MODE = 0x23,
	BH2_SET_MAC_EVENT_REPORTING = 0x24,
	BH2_GET_MLME_TIMEOUTS = 0x25,
	BH2_SET_MLME_TIMEOUTS = 0x26,
	BH2_SET_DTI_BEAMFORMING = 0x27,
	BH2_SET_LOCATION_INFORMATION = 0x28,
	BH2_GET_LOCATION_INFORMATION = 0x29,
	BH2_SET_TIMING_DELAY = 0x2a,
	BH2_GET_TIMING_DELAY = 0x2b,
	BH2_GET_TIMING_ADVANCE = 0x2c,

};

/* List of vendor event sub-cmds. This index is sent as the sub-command
 * within a vendor event report
 */
enum bh2_vendor_events {
	BH2_MAC_EVENT_REPORT = 0x00
};

#define	BMI_STATISTICS_FORMAT_VERSION	(1)

/*! @brief  Vendor format general statistics
 *
 *  Describes general statistical information reported for the
 *  Hydra modem.
 *
 *  May include optional developer statistics, which are passed as
 *  a binary blob only.
 */
struct bmi_general_statistics {
	s8   bh2_temperature;
	u8   reserved;
	u16  additional_len; //!< Length of any additional statistics

	//!< Additional statistics - this MUST be the last field
	u8  additional_data[0];
} __packed;

/*! @brief  Vendor format PCP statistics
 *
 *  Describes statistical information reported for a PCP
 *  which can be seen by the Hydra modem.
 *
 *  May include optional developer statistics, which are passed as
 *  a binary blob only.
 */
struct bmi_pcp_statistics {
	u8   pcp_mac[BH2_MAC_LEN];
	u8   reserved[2];
	s16  beacon_average_rcpi;
	s16  beacon_average_rssi;
	u32  beacon_count;
	u32  beacon_loss_count;
	s16  beacon_average_atten;
	s16  beacon_strongest_rcpi_last_bti;
	s16  beacon_strongest_atten_last_bti;
	u8   beacon_strongest_sector_last_bti;
	u8   reserved2;
	u16  additional_len; //!< Length of any additional statistics

	//!< Additional statistics - this MUST be the last field
	u8   additional_data[0];
} __packed;

/*! @brief  Connection STA statistical data
 *
 *  Reports statistics regarding a connection between the local Hydra modem
 *  and a remote STA that are only recorded at the STA.
 */
struct bmi_connection_sta_statistics_event {
	// Placeholder
} __packed;

/*! @brief  Connection PCP statistical data
 *
 *  Reports statistics regarding a connection between the local Hydra modem
 *  and a remote STA that are only recorded at the PCP.
 */
struct bmi_connection_pcp_statistics_event {
	// Placeholder
} __packed;

/*! @brief  Vendor format connection statistics
 *
 *  Describes statistical information reported for a connection
 *  between the local Hydra modem and a remote STA.
 *
 *  May include optional developer statistics, which are passed as
 *  a binary blob only.
 */
struct bmi_connection_statistics {
	u8   sta_mac[BH2_MAC_LEN];
	s16  current_rcpi;
	s16  average_rcpi;
	s16  current_rssi;
	s16  average_rssi;
	s16  current_snr;
	s16  average_snr;
	u16  mpdu_per;
	u16  tx_missed_ack_rate;
	u8   rx_mcs;
	u8   tx_mcs;
	u8   rx_sector_id;
	u8   tx_sector_id;
	u8   reserved[2];
	u32  inactive_time;
	u32  sched_src_sp_num_blocks;
	u32  sched_src_sp_duration;
	u32  sched_src_cbap_num_blocks;
	u32  sched_src_cbap_duration;
	u32  sched_dest_sp_num_blocks;
	u32  sched_dest_sp_duration;
	u32  sched_dest_cbap_num_blocks;
	u32  sched_dest_cbap_duration;
	u64  bytes_sent;
	u32  failed_announce_frames;
	u32  successful_announce_frames;
	u32  num_tx_announce_frames;
	u64  cir_tsf;
	s8   cir_data[CIR_DATA_LEN];
	u8   pcp_mode; //!< Remote STA is operating as a PCP
	u8   reserved2[3];
	union {
		struct bmi_connection_sta_statistics_event sta;
		struct bmi_connection_pcp_statistics_event pcp;
	};
	u64  packets_sent;
	u64  bytes_tx;
	u64  bytes_tx_mac;

	s16  current_snr_gi64;	// as measured over the Gi64 sequence
	s16  average_snr_gi64;	// as measured over the Gi64 sequence

	s16  current_atten;	//!< current AGC attenuation applied
	s16  average_atten;	//!< average AGC attenuation applied

	/*
	 * Strongest TXSS and RXSS sectors in the last BTI.
	 *
	 * SNR and RCPI values are reports from the link partner,
	 * received in the SSW feedback frames.
	 */
	s16  txss_strongest_snr_last_bti;
	s16  txss_strongest_rcpi_last_bti;
	s16  rxss_strongest_snr_last_bti;
	s16  rxss_strongest_rcpi_last_bti;
	u8   txss_strongest_sector_last_bti;
	u8   rxss_strongest_sector_last_bti;

	u32  txss_successful_frames;
	u32  rxss_successful_frames;

	u64  num_mpdu_rx;	// number of MPDUs received
	u64  num_mpdu_tx;	// number of MPDUs transmitted

	u16  additional_len; //!< Length of any additional statistics

	//!< Additional statistics - this MUST be the last field
	u8   additional_data[0];
} __packed;

/*! @brief Vendor statistics
 *
 *  Describes the vendor statistics returned in binary mode. This is a
 *  variable length structure, with the data field expanded to include
 *  the requested fields, in general, PCP, connection order.
 */
struct vendor_statistics {
	u64 timestamp; //!< TSF at which the statistics were reported
	u8  version; //!< statistics format version
	u8  general; //!< non zero if general statistics are reported
	u8  num_pcps; //!< the number of PCP entries reported
	u8  num_connections; //!< the number of connections entries reported

	/**
	 * general statistics if general is non zero - see
	 *   struct bmi_general_statistics
	 * followed by num_pcps PCP statistics - see
	 *   struct bmi_pcp_statistics
	 * followed by num_connections connection statistics - see
	 *   struct  bmi_connection_statistics
	 */
	u8 data[0];
} __packed;

/*! @brief  Vendor phy rx DCO parameters
 *
 *  RX DC offset LUT entries.
 *
 *  Complex Q1.8 format
 */
struct bmi_phy_rx_dco_params {
	s16 i[BMI_NUM_RX_DC_OFFSET_ENTRIES];
	s16 q[BMI_NUM_RX_DC_OFFSET_ENTRIES];
} __packed;

/*! @brief  Vendor phy tx DCO parameters
 *
 *  TX DC offset entry.
 *
 *  Complex Q1.13 format
 */
struct bmi_phy_tx_dco_params {
	s16 i;
	s16 q;
} __packed;

/*! @brief  Vendor phy phase correction parameters
 *
 *  RX and TX phase correction factor.
 *
 *  Complex Q2.8 format
 */
struct bmi_phy_phase_corr_params {
	s16 i;
	s16 q;
} __packed;

/*! @brief  Vendor phy equaliser filter parameters
 *
 *  RX and TX equaliser filter taps.
 *
 *  Complex Q1.10 format
 */
struct bmi_phy_eq_filter_params {
	s16 tap[BMI_NUM_EQ_FILTER_TAPS];
} __packed;

/*! @brief  MCS control mode
 *
 *  Enumerates the MCS control modes a station can operate under.
 */
enum bmi_mcs_control_mode {
	BMI_MCS_CONTROL_AUTOMATIC = 0,
	BMI_MCS_CONTROL_AUTOMATIC_FCS,
	BMI_MCS_CONTROL_AUTOMATIC_SNR,
	BMI_MCS_CONTROL_FIXED
};

/*! @brief  BMI block ack type
 *
 *  Enumerates the block ack types supported.
 */
enum bmi_block_ack_type {
	  BMI_BA_VARIANT_BASIC = 0,
	  BMI_BA_VARIANT_COMPRESSED,
	  BMI_BA_VARIANT_EXTENDED_COMPRESSED,
	  BMI_BA_VARIANT_MULTI_TID
};

/*! @brief  Band configuration
 *
 *  Enumerates the supported bands
 */
enum bmi_operating_band {
	BMI_BAND_60GHZ = 0
};

/*! @brief  Sample Rate types
 *
 *  Enumerates the supported sample rate types.
 */
enum bmi_sample_rate_type {
	BMI_SAMPLE_RATE_TYPE_FULL = 1,
	BMI_SAMPLE_RATE_TYPE_HALF = 2,
	BMI_SAMPLE_RATE_TYPE_THIRD = 3,
	BMI_SAMPLE_RATE_TYPE_QUARTER = 4
};

/*! @brief  Bandwidth types
 *
 *  Enumerates the supported bandwidth types.
 */
enum bmi_bandwidth_type {
	BMI_BANDWIDTH_TYPE_FULL = 1,
	BMI_BANDWIDTH_TYPE_HALF = 2,
	BMI_BANDWIDTH_TYPE_QUARTER = 4
};

/*! @brief  Subchannel types
 *
 *  Enumerates the supported subchannel types.
 */
enum bmi_subchannel_type {
	BMI_SUBCHANNEL_TYPE_FULL = 0,
	BMI_SUBCHANNEL_TYPE_HALF,
	BMI_SUBCHANNEL_TYPE_HALF_R,
	BMI_SUBCHANNEL_TYPE_HALF_L,
	BMI_SUBCHANNEL_TYPE_QUARTER,
	BMI_SUBCHANNEL_TYPE_QUARTER_R_0,
	BMI_SUBCHANNEL_TYPE_QUARTER_R_1,
	BMI_SUBCHANNEL_TYPE_QUARTER_L_0,
	BMI_SUBCHANNEL_TYPE_QUARTER_L_1
};

/*! @brief  BWT vendor specific IE sub-element IDs
 *
 *  Enumerates the BWT specific sub-elements which can be sent
 *  in a vendor specific IE.
 */
enum bmi_bwt_vendor_sub_element_id_type {
	BMI_LINK_ADAPTATION_SUB_ELEM_ID = 1,
	BMI_SUB_CHANNEL_LIST_SUB_ELEM_ID,
	BMI_SLOTTED_TDD_CONFIG_SUB_ELEM_ID,
	BMI_LOCATION_INFO_SUB_ELEM_ID
};

/*! @brief  Hydra MAC event IDs
 *
 *  Enumerates the various MAC event Ids
 */
enum bmi_mac_event_id_type {
	BH2_MAC_STA_ASSOCIATED_EVT_ID = 0,
	BH2_MAC_STA_DISASSOCIATED_EVT_ID,
	BH2_MAC_STA_CONNECTED_EVT_ID,
	BH2_MAC_STA_DISCONNECTED_EVT_ID,
	BH2_MAC_STA_RECONNECTED_EVT_ID,
	BH2_MAC_EVENT_QUEUE_FULL_EVT_ID
};

/*! @brief  Hydra MAC event priorities
 *
 *  Enumerates the various priority levels for an event.
 */
enum bmi_mac_event_priority_type {
	BH2_MAC_FATAL_EVENT_TYPE = 0,	//!< Fatal condition detected
	BH2_MAC_ERROR_EVENT_TYPE,	//!< Erroneous operation detected
	BH2_MAC_WARNING_EVENT_TYPE,	//!< Unexpected operation detected
	BH2_MAC_ALERT_EVENT_TYPE,	//!< Threshold type warning conditions
	BH2_MAC_INFO_EVENT_TYPE		//!< Normal operation event
};

/*! @brief  BWT MAC event report entry
 *
 *  Describes a single event being reported.
 */
struct bmi_mac_event_report {
	u32 id; //!< MAC event id - see enum bmi_mac_event_id
	u8 priority; //!< event priority - see enum bmi_mac_evt_priority
	u8 spare;
	u8 mac[BH2_MAC_LEN]; //!< MAC address related to the event
	u64 timestamp; //!< event generation time, in us
	u32 event_data[BMI_EVENT_DATA_WORDS]; //!< data related to the event
} __packed;

#endif /* __BMI_VENDOR_H__ */
