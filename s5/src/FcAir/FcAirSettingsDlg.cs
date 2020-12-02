using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace UpgenConsole.FcAir
{
    public partial class FcAirSettingsDlg : Form
    {
        FcAirSettings m_Settings;

        public FcAirSettings Settings
        {
            get { return m_Settings; }
        }

        public FcAirSettingsDlg(FcAirSettings settings)
        {
            InitializeComponent();
            m_Settings = settings;

            this.numericUpDownChargeVoltageAt25C.Value = Convert.ToDecimal(settings.getValue(FcAirSettings.Items.ChargeVoltageAt25C));
            this.numericUpDownDeadVoltage.Value = Convert.ToDecimal(settings.getValue(FcAirSettings.Items.DeadVoltage));
            this.numericUpDownMaxChargeTemp.Value = Convert.ToDecimal(settings.getValue(FcAirSettings.Items.MaxChargeTemp));
            this.numericUpDownMinChargeTemp.Value = Convert.ToDecimal(settings.getValue(FcAirSettings.Items.MinChargeTemp));
            this.numericUpDownChargeVoltageAt0C.Value = Convert.ToDecimal(settings.getValue(FcAirSettings.Items.ChargeVoltageAt0C));
            this.numericUpDownMaxChargeCurrent.Value = Convert.ToDecimal(settings.getValue(FcAirSettings.Items.MaxChargeCurrent));
            this.numericUpDownMaxBatteryVoltage.Value = Convert.ToDecimal(settings.getValue(FcAirSettings.Items.MaxBatteryVoltage));
        }

        private void button1_Click(object sender, EventArgs e)
        {
            m_Settings.setValue(FcAirSettings.Items.ChargeVoltageAt25C, Convert.ToDouble(this.numericUpDownChargeVoltageAt25C.Value));
            m_Settings.setValue(FcAirSettings.Items.DeadVoltage, Convert.ToDouble(this.numericUpDownDeadVoltage.Value));
            m_Settings.setValue(FcAirSettings.Items.MaxChargeTemp, Convert.ToDouble(this.numericUpDownMaxChargeTemp.Value));
            m_Settings.setValue(FcAirSettings.Items.MinChargeTemp, Convert.ToDouble(this.numericUpDownMinChargeTemp.Value));
            m_Settings.setValue(FcAirSettings.Items.ChargeVoltageAt0C, Convert.ToDouble(this.numericUpDownChargeVoltageAt0C.Value));
            m_Settings.setValue(FcAirSettings.Items.MaxChargeCurrent, Convert.ToDouble(this.numericUpDownMaxChargeCurrent.Value));
            m_Settings.setValue(FcAirSettings.Items.MaxBatteryVoltage, Convert.ToDouble(this.numericUpDownMaxBatteryVoltage.Value));
        }
    }
}
