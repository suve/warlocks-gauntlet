﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace WGDataEditor
{
    public class AttributeDefinition
    {
        public AttributeDefinition()
        {
            Name = "New_Attribute";
            NameXml = "";
            Removable = true;
            Type = "";
        }

        [Category("Attributes"), Description("Editor-only name")]
        public string Name { get; set; }

        [Category("Attributes"), Description("Xml name")]
        public string NameXml { get; set; }

        [Category("Attributes"), Description("Type of attribute - can be changed in settings.xml"), TypeConverter(typeof(TypeConverter))]
        public string Type { get; set; }

        [Category("Attributes"), Description("If false, attribute cannot be removed - suggested for default attributes")]
        public bool Removable { get; set; }

        public class TypeConventer : StringConverter
        {
            public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
            {
                return true;
            }

            public override StandardValuesCollection
                     GetStandardValues(ITypeDescriptorContext context)
            {
                return new StandardValuesCollection(MainForm.Instance.Settings.Types);
            }
        } 

    }
}