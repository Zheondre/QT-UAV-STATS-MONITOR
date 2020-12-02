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
    public partial class FcAirLimitsDlg : Form
    {
        FcAirLimits m_Limits;

        public FcAirLimits Config
        {
            get { return m_Limits; }
        }

        public FcAirLimitsDlg(FcAirLimits limits)
        {
            InitializeComponent();

            m_Limits = limits;

            this.numericUpDownMaxBoardTemp.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.MaxBoardTemp));
            this.numericUpDownMaxExternalStackTemp.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.MaxExternalStackTemp));
            this.numericUpDownMaxInternalStackTemp.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.MaxInternalStackTemp));
            this.numericUpDownMaxConverterTemp.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.MaxConverterTemp));
            this.numericUpDownStackMinimumVoltage.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.StackMinimumVoltage));
            this.numericUpDownMaxH2Pressure.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.MaxH2Pressure));
            this.numericUpDownMaxStackCurrent.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.MaxStackCurrent));
            this.numericUpDownHighPressureErrorRemediateTime.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.HighPressureErrorRemediateTime));
            this.numericUpDownHighPressureErrorFaultTime.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.HighPressureErrorFaultTime));
            this.numericUpDownMinH2Pressure.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.MinH2Pressure));
            this.numericUpDownLowPressureErrorFaultTime.Value = Convert.ToDecimal(m_Limits.getValue(FcAirLimits.Items.LowPressureErrorFaultTime));
        }

        private void button1_Click(object sender, EventArgs e)
        {
            m_Limits.setValue(FcAirLimits.Items.MaxBoardTemp, Convert.ToDouble(this.numericUpDownMaxBoardTemp.Value));
            m_Limits.setValue(FcAirLimits.Items.MaxExternalStackTemp, Convert.ToDouble(this.numericUpDownMaxExternalStackTemp.Value));
            m_Limits.setValue(FcAirLimits.Items.MaxInternalStackTemp, Convert.ToDouble(this.numericUpDownMaxInternalStackTemp.Value));
            m_Limits.setValue(FcAirLimits.Items.MaxConverterTemp, Convert.ToDouble(this.numericUpDownMaxConverterTemp.Value));
            m_Limits.setValue(FcAirLimits.Items.StackMinimumVoltage, Convert.ToDouble(this.numericUpDownStackMinimumVoltage.Value));
            m_Limits.setValue(FcAirLimits.Items.MaxH2Pressure, Convert.ToDouble(this.numericUpDownMaxH2Pressure.Value));
            m_Limits.setValue(FcAirLimits.Items.MaxStackCurrent, Convert.ToDouble(this.numericUpDownMaxStackCurrent.Value));
            m_Limits.setValue(FcAirLimits.Items.LowPressureErrorFaultTime, Convert.ToDouble(this.numericUpDownLowPressureErrorFaultTime.Value));
            m_Limits.setValue(FcAirLimits.Items.HighPressureErrorRemediateTime, Convert.ToDouble(this.numericUpDownHighPressureErrorRemediateTime.Value));
            m_Limits.setValue(FcAirLimits.Items.HighPressureErrorFaultTime, Convert.ToDouble(this.numericUpDownHighPressureErrorFaultTime.Value));
            m_Limits.setValue(FcAirLimits.Items.MinH2Pressure, Convert.ToDouble(this.numericUpDownMinH2Pressure.Value));
        }
    }
}
