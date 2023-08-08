struct TempSensor : Service::TemperatureSensor
{
    SpanCharacteristic *temp;
    uint32_t timer = 0;

    TempSensor() : Service::TemperatureSensor()
    {

        double tempC = getTemp();
        temp = new Characteristic::CurrentTemperature(tempC);
    }

    void loop()
    {
        if (millis() - timer > 5000)
        { // only sample every 5 seconds
            timer = millis();

            double tempC = getTemp();

            if (abs(temp->getVal<double>() - tempC) > 0.5)
            {
                temp->setVal(tempC);
            }
        }
    }
    double getTemp()
    {
        if (!bme.begin())
        {
            Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
            while (1)
            {
            }
        }

        if (!bme.performReading())
        {
            Serial.println("Failed to perform reading :(");
        }
        
        double t = bme.temperature;
        return (t);
    }
};
